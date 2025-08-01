// Copyright 2008 Google Inc.
// All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Type and function utilities for implementing parameterized tests.

// GOOGLETEST_CM0001 DO NOT DELETE

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PARAM_UTIL_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PARAM_UTIL_H_

#include "gtest/gtest-printers.h"
#include "gtest/internal/gtest-internal.h"
#include "gtest/internal/gtest-linked_ptr.h"
#include "gtest/internal/gtest-port.h"

#include <ctype.h>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

namespace testing {

// Input to a parameterized test name generator, describing a test parameter.
// Consists of the parameter value and the integer parameter index.
template<class ParamType> struct TestParamInfo {
    TestParamInfo(const ParamType& a_param, size_t an_index)
        : param(a_param), index(an_index) {}
    ParamType param;
    size_t index;
};

// A builtin parameterized test name generator which returns the result of
// testing::PrintToString.
struct PrintToStringParamName {
    template<class ParamType>
    std::string operator()(const TestParamInfo<ParamType>& info) const {
        return PrintToString(info.param);
    }
};

namespace internal {

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Outputs a message explaining invalid registration of different
// fixture class for the same test case. This may happen when
// TEST_P macro is used to define two tests with the same name
// but in different namespaces.
GTEST_API_ void ReportInvalidTestCaseType(const char* test_case_name,
                                          CodeLocation code_location);

template<typename> class ParamGeneratorInterface;
template<typename> class ParamGenerator;

// Interface for iterating over elements provided by an implementation
// of ParamGeneratorInterface<T>.
template<typename T> class ParamIteratorInterface {
   public:
    virtual ~ParamIteratorInterface() {}
    // A pointer to the base generator instance.
    // Used only for the purposes of iterator comparison
    // to make sure that two iterators belong to the same generator.
    virtual const ParamGeneratorInterface<T>* BaseGenerator() const = 0;
    // Advances iterator to point to the next element
    // provided by the generator. The caller is responsible
    // for not calling Advance() on an iterator equal to
    // BaseGenerator()->End().
    virtual void Advance() = 0;
    // Clones the iterator object. Used for implementing copy semantics
    // of ParamIterator<T>.
    virtual ParamIteratorInterface* Clone() const = 0;
    // Dereferences the current iterator and provides (read-only) access
    // to the pointed value. It is the caller's responsibility not to call
    // Current() on an iterator equal to BaseGenerator()->End().
    // Used for implementing ParamGenerator<T>::operator*().
    virtual const T* Current() const = 0;
    // Determines whether the given iterator and other point to the same
    // element in the sequence generated by the generator.
    // Used for implementing ParamGenerator<T>::operator==().
    virtual bool Equals(const ParamIteratorInterface& other) const = 0;
};

// Class iterating over elements provided by an implementation of
// ParamGeneratorInterface<T>. It wraps ParamIteratorInterface<T>
// and implements the const forward iterator concept.
template<typename T> class ParamIterator {
   public:
    typedef T value_type;
    typedef const T& reference;
    typedef ptrdiff_t difference_type;

    // ParamIterator assumes ownership of the impl_ pointer.
    ParamIterator(const ParamIterator& other) : impl_(other.impl_->Clone()) {}
    ParamIterator& operator=(const ParamIterator& other) {
        if (this != &other) impl_.reset(other.impl_->Clone());
        return *this;
    }

    const T& operator*() const { return *impl_->Current(); }
    const T* operator->() const { return impl_->Current(); }
    // Prefix version of operator++.
    ParamIterator& operator++() {
        impl_->Advance();
        return *this;
    }
    // Postfix version of operator++.
    ParamIterator operator++(int /*unused*/) {
        ParamIteratorInterface<T>* clone = impl_->Clone();
        impl_->Advance();
        return ParamIterator(clone);
    }
    bool operator==(const ParamIterator& other) const {
        return impl_.get() == other.impl_.get() || impl_->Equals(*other.impl_);
    }
    bool operator!=(const ParamIterator& other) const {
        return !(*this == other);
    }

   private:
    friend class ParamGenerator<T>;
    explicit ParamIterator(ParamIteratorInterface<T>* impl) : impl_(impl) {}
    scoped_ptr<ParamIteratorInterface<T>> impl_;
};

// ParamGeneratorInterface<T> is the binary interface to access generators
// defined in other translation units.
template<typename T> class ParamGeneratorInterface {
   public:
    typedef T ParamType;

    virtual ~ParamGeneratorInterface() {}

    // Generator interface definition
    virtual ParamIteratorInterface<T>* Begin() const = 0;
    virtual ParamIteratorInterface<T>* End() const = 0;
};

// Wraps ParamGeneratorInterface<T> and provides general generator syntax
// compatible with the STL Container concept.
// This class implements copy initialization semantics and the contained
// ParamGeneratorInterface<T> instance is shared among all copies
// of the original object. This is possible because that instance is immutable.
template<typename T> class ParamGenerator {
   public:
    typedef ParamIterator<T> iterator;

    explicit ParamGenerator(ParamGeneratorInterface<T>* impl) : impl_(impl) {}
    ParamGenerator(const ParamGenerator& other) : impl_(other.impl_) {}

    ParamGenerator& operator=(const ParamGenerator& other) {
        impl_ = other.impl_;
        return *this;
    }

    iterator begin() const { return iterator(impl_->Begin()); }
    iterator end() const { return iterator(impl_->End()); }

   private:
    linked_ptr<const ParamGeneratorInterface<T>> impl_;
};

// Generates values from a range of two comparable values. Can be used to
// generate sequences of user-defined types that implement operator+() and
// operator<().
// This class is used in the Range() function.
template<typename T, typename IncrementT> class RangeGenerator
    : public ParamGeneratorInterface<T> {
   public:
    RangeGenerator(T begin, T end, IncrementT step)
        : begin_(begin),
          end_(end),
          step_(step),
          end_index_(CalculateEndIndex(begin, end, step)) {}
    virtual ~RangeGenerator() {}

    virtual ParamIteratorInterface<T>* Begin() const {
        return new Iterator(this, begin_, 0, step_);
    }
    virtual ParamIteratorInterface<T>* End() const {
        return new Iterator(this, end_, end_index_, step_);
    }

   private:
    class Iterator : public ParamIteratorInterface<T> {
       public:
        Iterator(const ParamGeneratorInterface<T>* base, T value, int index,
                 IncrementT step)
            : base_(base), value_(value), index_(index), step_(step) {}
        virtual ~Iterator() {}

        virtual const ParamGeneratorInterface<T>* BaseGenerator() const {
            return base_;
        }
        virtual void Advance() {
            value_ = static_cast<T>(value_ + step_);
            index_++;
        }
        virtual ParamIteratorInterface<T>* Clone() const {
            return new Iterator(*this);
        }
        virtual const T* Current() const { return &value_; }
        virtual bool Equals(const ParamIteratorInterface<T>& other) const {
            // Having the same base generator guarantees that the other
            // iterator is of the same type and we can downcast.
            GTEST_CHECK_(BaseGenerator() == other.BaseGenerator())
                << "The program attempted to compare iterators "
                << "from different generators." << std::endl;
            const int other_index =
                CheckedDowncastToActualType<const Iterator>(&other)->index_;
            return index_ == other_index;
        }

       private:
        Iterator(const Iterator& other)
            : ParamIteratorInterface<T>(),
              base_(other.base_),
              value_(other.value_),
              index_(other.index_),
              step_(other.step_) {}

        // No implementation - assignment is unsupported.
        void operator=(const Iterator& other);

        const ParamGeneratorInterface<T>* const base_;
        T value_;
        int index_;
        const IncrementT step_;
    };  // class RangeGenerator::Iterator

    static int CalculateEndIndex(const T& begin, const T& end,
                                 const IncrementT& step) {
        int end_index = 0;
        for (T i = begin; i < end; i = static_cast<T>(i + step)) end_index++;
        return end_index;
    }

    // No implementation - assignment is unsupported.
    void operator=(const RangeGenerator& other);

    const T begin_;
    const T end_;
    const IncrementT step_;
    // The index for the end() iterator. All the elements in the generated
    // sequence are indexed (0-based) to aid iterator comparison.
    const int end_index_;
};  // class RangeGenerator

// Generates values from a pair of STL-style iterators. Used in the
// ValuesIn() function. The elements are copied from the source range
// since the source can be located on the stack, and the generator
// is likely to persist beyond that stack frame.
template<typename T> class ValuesInIteratorRangeGenerator
    : public ParamGeneratorInterface<T> {
   public:
    template<typename ForwardIterator>
    ValuesInIteratorRangeGenerator(ForwardIterator begin, ForwardIterator end)
        : container_(begin, end) {}
    virtual ~ValuesInIteratorRangeGenerator() {}

    virtual ParamIteratorInterface<T>* Begin() const {
        return new Iterator(this, container_.begin());
    }
    virtual ParamIteratorInterface<T>* End() const {
        return new Iterator(this, container_.end());
    }

   private:
    typedef typename ::std::vector<T> ContainerType;

    class Iterator : public ParamIteratorInterface<T> {
       public:
        Iterator(const ParamGeneratorInterface<T>* base,
                 typename ContainerType::const_iterator iterator)
            : base_(base), iterator_(iterator) {}
        virtual ~Iterator() {}

        virtual const ParamGeneratorInterface<T>* BaseGenerator() const {
            return base_;
        }
        virtual void Advance() {
            ++iterator_;
            value_.reset();
        }
        virtual ParamIteratorInterface<T>* Clone() const {
            return new Iterator(*this);
        }
        // We need to use cached value referenced by iterator_ because
        // *iterator_ can return a temporary object (and of type other then T),
        // so just having "return &*iterator_;" doesn't work. value_ is updated
        // here and not in Advance() because Advance() can advance iterator_
        // beyond the end of the range, and we cannot detect that fact. The
        // client code, on the other hand, is responsible for not calling
        // Current() on an out-of-range iterator.
        virtual const T* Current() const {
            if (value_.get() == NULL) value_.reset(new T(*iterator_));
            return value_.get();
        }
        virtual bool Equals(const ParamIteratorInterface<T>& other) const {
            // Having the same base generator guarantees that the other
            // iterator is of the same type and we can downcast.
            GTEST_CHECK_(BaseGenerator() == other.BaseGenerator())
                << "The program attempted to compare iterators "
                << "from different generators." << std::endl;
            return iterator_ ==
                   CheckedDowncastToActualType<const Iterator>(&other)
                       ->iterator_;
        }

       private:
        Iterator(const Iterator& other)
            // The explicit constructor call suppresses a false warning
            // emitted by gcc when supplied with the -Wextra option.
            : ParamIteratorInterface<T>(),
              base_(other.base_),
              iterator_(other.iterator_) {}

        const ParamGeneratorInterface<T>* const base_;
        typename ContainerType::const_iterator iterator_;
        // A cached value of *iterator_. We keep it here to allow access by
        // pointer in the wrapping iterator's operator->().
        // value_ needs to be mutable to be accessed in Current().
        // Use of scoped_ptr helps manage cached value's lifetime,
        // which is bound by the lifespan of the iterator itself.
        mutable scoped_ptr<const T> value_;
    };  // class ValuesInIteratorRangeGenerator::Iterator

    // No implementation - assignment is unsupported.
    void operator=(const ValuesInIteratorRangeGenerator& other);

    const ContainerType container_;
};  // class ValuesInIteratorRangeGenerator

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Default parameterized test name generator, returns a string containing the
// integer test parameter index.
template<class ParamType>
std::string DefaultParamName(const TestParamInfo<ParamType>& info) {
    Message name_stream;
    name_stream << info.index;
    return name_stream.GetString();
}

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Parameterized test name overload helpers, which help the
// INSTANTIATE_TEST_CASE_P macro choose between the default parameterized
// test name generator and user param name generator.
template<class ParamType, class ParamNameGenFunctor>
ParamNameGenFunctor GetParamNameGen(ParamNameGenFunctor func) {
    return func;
}

template<class ParamType> struct ParamNameGenFunc {
    typedef std::string Type(const TestParamInfo<ParamType>&);
};

template<class ParamType>
typename ParamNameGenFunc<ParamType>::Type* GetParamNameGen() {
    return DefaultParamName;
}

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Stores a parameter value and later creates tests parameterized with that
// value.
template<class TestClass> class ParameterizedTestFactory
    : public TestFactoryBase {
   public:
    typedef typename TestClass::ParamType ParamType;
    explicit ParameterizedTestFactory(ParamType parameter)
        : parameter_(parameter) {}
    virtual Test* CreateTest() {
        TestClass::SetParam(&parameter_);
        return new TestClass();
    }

   private:
    const ParamType parameter_;

    GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestFactory);
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// TestMetaFactoryBase is a base class for meta-factories that create
// test factories for passing into MakeAndRegisterTestInfo function.
template<class ParamType> class TestMetaFactoryBase {
   public:
    virtual ~TestMetaFactoryBase() {}

    virtual TestFactoryBase* CreateTestFactory(ParamType parameter) = 0;
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// TestMetaFactory creates test factories for passing into
// MakeAndRegisterTestInfo function. Since MakeAndRegisterTestInfo receives
// ownership of test factory pointer, same factory object cannot be passed
// into that method twice. But ParameterizedTestCaseInfo is going to call
// it for each Test/Parameter value combination. Thus it needs meta factory
// creator class.
template<class TestCase> class TestMetaFactory
    : public TestMetaFactoryBase<typename TestCase::ParamType> {
   public:
    typedef typename TestCase::ParamType ParamType;

    TestMetaFactory() {}

    virtual TestFactoryBase* CreateTestFactory(ParamType parameter) {
        return new ParameterizedTestFactory<TestCase>(parameter);
    }

   private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(TestMetaFactory);
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// ParameterizedTestCaseInfoBase is a generic interface
// to ParameterizedTestCaseInfo classes. ParameterizedTestCaseInfoBase
// accumulates test information provided by TEST_P macro invocations
// and generators provided by INSTANTIATE_TEST_CASE_P macro invocations
// and uses that information to register all resulting test instances
// in RegisterTests method. The ParameterizeTestCaseRegistry class holds
// a collection of pointers to the ParameterizedTestCaseInfo objects
// and calls RegisterTests() on each of them when asked.
class ParameterizedTestCaseInfoBase {
   public:
    virtual ~ParameterizedTestCaseInfoBase() {}

    // Base part of test case name for display purposes.
    virtual const std::string& GetTestCaseName() const = 0;
    // Test case id to verify identity.
    virtual TypeId GetTestCaseTypeId() const = 0;
    // UnitTest class invokes this method to register tests in this
    // test case right before running them in RUN_ALL_TESTS macro.
    // This method should not be called more then once on any single
    // instance of a ParameterizedTestCaseInfoBase derived class.
    virtual void RegisterTests() = 0;

   protected:
    ParameterizedTestCaseInfoBase() {}

   private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestCaseInfoBase);
};

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// ParameterizedTestCaseInfo accumulates tests obtained from TEST_P
// macro invocations for a particular test case and generators
// obtained from INSTANTIATE_TEST_CASE_P macro invocations for that
// test case. It registers tests with all values generated by all
// generators when asked.
template<class TestCase> class ParameterizedTestCaseInfo
    : public ParameterizedTestCaseInfoBase {
   public:
    // ParamType and GeneratorCreationFunc are private types but are required
    // for declarations of public methods AddTestPattern() and
    // AddTestCaseInstantiation().
    typedef typename TestCase::ParamType ParamType;
    // A function that returns an instance of appropriate generator type.
    typedef ParamGenerator<ParamType>(GeneratorCreationFunc)();
    typedef typename ParamNameGenFunc<ParamType>::Type ParamNameGeneratorFunc;

    explicit ParameterizedTestCaseInfo(const char* name,
                                       CodeLocation code_location)
        : test_case_name_(name), code_location_(code_location) {}

    // Test case base name for display purposes.
    virtual const std::string& GetTestCaseName() const {
        return test_case_name_;
    }
    // Test case id to verify identity.
    virtual TypeId GetTestCaseTypeId() const { return GetTypeId<TestCase>(); }
    // TEST_P macro uses AddTestPattern() to record information
    // about a single test in a LocalTestInfo structure.
    // test_case_name is the base name of the test case (without invocation
    // prefix). test_base_name is the name of an individual test without
    // parameter index. For the test SequenceA/FooTest.DoBar/1 FooTest is
    // test case base name and DoBar is test base name.
    void AddTestPattern(const char* test_case_name, const char* test_base_name,
                        TestMetaFactoryBase<ParamType>* meta_factory) {
        tests_.push_back(linked_ptr<TestInfo>(
            new TestInfo(test_case_name, test_base_name, meta_factory)));
    }
    // INSTANTIATE_TEST_CASE_P macro uses AddGenerator() to record information
    // about a generator.
    int AddTestCaseInstantiation(const std::string& instantiation_name,
                                 GeneratorCreationFunc* func,
                                 ParamNameGeneratorFunc* name_func,
                                 const char* file, int line) {
        instantiations_.push_back(
            InstantiationInfo(instantiation_name, func, name_func, file, line));
        return 0;  // Return value used only to run this method in namespace
                   // scope.
    }
    // UnitTest class invokes this method to register tests in this test case
    // test cases right before running tests in RUN_ALL_TESTS macro.
    // This method should not be called more then once on any single
    // instance of a ParameterizedTestCaseInfoBase derived class.
    // UnitTest has a guard to prevent from calling this method more then once.
    virtual void RegisterTests() {
        for (typename TestInfoContainer::iterator test_it = tests_.begin();
             test_it != tests_.end(); ++test_it) {
            linked_ptr<TestInfo> test_info = *test_it;
            for (typename InstantiationContainer::iterator gen_it =
                     instantiations_.begin();
                 gen_it != instantiations_.end(); ++gen_it) {
                const std::string& instantiation_name = gen_it->name;
                ParamGenerator<ParamType> generator((*gen_it->generator)());
                ParamNameGeneratorFunc* name_func = gen_it->name_func;
                const char* file = gen_it->file;
                int line = gen_it->line;

                std::string test_case_name;
                if (!instantiation_name.empty())
                    test_case_name = instantiation_name + "/";
                test_case_name += test_info->test_case_base_name;

                size_t i = 0;
                std::set<std::string> test_param_names;
                for (typename ParamGenerator<ParamType>::iterator param_it =
                         generator.begin();
                     param_it != generator.end(); ++param_it, ++i) {
                    Message test_name_stream;

                    std::string param_name =
                        name_func(TestParamInfo<ParamType>(*param_it, i));

                    GTEST_CHECK_(IsValidParamName(param_name))
                        << "Parameterized test name '" << param_name
                        << "' is invalid, in " << file << " line " << line
                        << std::endl;

                    GTEST_CHECK_(test_param_names.count(param_name) == 0)
                        << "Duplicate parameterized test name '" << param_name
                        << "', in " << file << " line " << line << std::endl;

                    test_param_names.insert(param_name);

                    test_name_stream << test_info->test_base_name << "/"
                                     << param_name;
                    MakeAndRegisterTestInfo(
                        test_case_name.c_str(),
                        test_name_stream.GetString().c_str(),
                        NULL,  // No type parameter.
                        PrintToString(*param_it).c_str(), code_location_,
                        GetTestCaseTypeId(), TestCase::SetUpTestCase,
                        TestCase::TearDownTestCase,
                        test_info->test_meta_factory->CreateTestFactory(
                            *param_it));
                }  // for param_it
            }  // for gen_it
        }  // for test_it
    }  // RegisterTests

   private:
    // LocalTestInfo structure keeps information about a single test registered
    // with TEST_P macro.
    struct TestInfo {
        TestInfo(const char* a_test_case_base_name,
                 const char* a_test_base_name,
                 TestMetaFactoryBase<ParamType>* a_test_meta_factory)
            : test_case_base_name(a_test_case_base_name),
              test_base_name(a_test_base_name),
              test_meta_factory(a_test_meta_factory) {}

        const std::string test_case_base_name;
        const std::string test_base_name;
        const scoped_ptr<TestMetaFactoryBase<ParamType>> test_meta_factory;
    };
    typedef ::std::vector<linked_ptr<TestInfo>> TestInfoContainer;
    // Records data received from INSTANTIATE_TEST_CASE_P macros:
    //  <Instantiation name, Sequence generator creation function,
    //     Name generator function, Source file, Source line>
    struct InstantiationInfo {
        InstantiationInfo(const std::string& name_in,
                          GeneratorCreationFunc* generator_in,
                          ParamNameGeneratorFunc* name_func_in,
                          const char* file_in, int line_in)
            : name(name_in),
              generator(generator_in),
              name_func(name_func_in),
              file(file_in),
              line(line_in) {}

        std::string name;
        GeneratorCreationFunc* generator;
        ParamNameGeneratorFunc* name_func;
        const char* file;
        int line;
    };
    typedef ::std::vector<InstantiationInfo> InstantiationContainer;

    static bool IsValidParamName(const std::string& name) {
        // Check for empty string
        if (name.empty()) return false;

        // Check for invalid characters
        for (std::string::size_type index = 0; index < name.size(); ++index) {
            if (!isalnum(name[index]) && name[index] != '_') return false;
        }

        return true;
    }

    const std::string test_case_name_;
    CodeLocation code_location_;
    TestInfoContainer tests_;
    InstantiationContainer instantiations_;

    GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestCaseInfo);
};  // class ParameterizedTestCaseInfo

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// ParameterizedTestCaseRegistry contains a map of ParameterizedTestCaseInfoBase
// classes accessed by test case names. TEST_P and INSTANTIATE_TEST_CASE_P
// macros use it to locate their corresponding ParameterizedTestCaseInfo
// descriptors.
class ParameterizedTestCaseRegistry {
   public:
    ParameterizedTestCaseRegistry() {}
    ~ParameterizedTestCaseRegistry() {
        for (TestCaseInfoContainer::iterator it = test_case_infos_.begin();
             it != test_case_infos_.end(); ++it) {
            delete *it;
        }
    }

    // Looks up or creates and returns a structure containing information about
    // tests and instantiations of a particular test case.
    template<class TestCase>
    ParameterizedTestCaseInfo<TestCase>* GetTestCasePatternHolder(
        const char* test_case_name, CodeLocation code_location) {
        ParameterizedTestCaseInfo<TestCase>* typed_test_info = NULL;
        for (TestCaseInfoContainer::iterator it = test_case_infos_.begin();
             it != test_case_infos_.end(); ++it) {
            if ((*it)->GetTestCaseName() == test_case_name) {
                if ((*it)->GetTestCaseTypeId() != GetTypeId<TestCase>()) {
                    // Complain about incorrect usage of Google Test facilities
                    // and terminate the program since we cannot guaranty
                    // correct test case setup and tear-down in this case.
                    ReportInvalidTestCaseType(test_case_name, code_location);
                    posix::Abort();
                } else {
                    // At this point we are sure that the object we found is of
                    // the same type we are looking for, so we downcast it to
                    // that type without further checks.
                    typed_test_info = CheckedDowncastToActualType<
                        ParameterizedTestCaseInfo<TestCase>>(*it);
                }
                break;
            }
        }
        if (typed_test_info == NULL) {
            typed_test_info = new ParameterizedTestCaseInfo<TestCase>(
                test_case_name, code_location);
            test_case_infos_.push_back(typed_test_info);
        }
        return typed_test_info;
    }
    void RegisterTests() {
        for (TestCaseInfoContainer::iterator it = test_case_infos_.begin();
             it != test_case_infos_.end(); ++it) {
            (*it)->RegisterTests();
        }
    }

   private:
    typedef ::std::vector<ParameterizedTestCaseInfoBase*> TestCaseInfoContainer;

    TestCaseInfoContainer test_case_infos_;

    GTEST_DISALLOW_COPY_AND_ASSIGN_(ParameterizedTestCaseRegistry);
};

}  // namespace internal
}  // namespace testing

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PARAM_UTIL_H_
