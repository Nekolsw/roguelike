@echo off
for /R %%F in (*.cpp *.h) do (
    "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\bin\clang-format.exe" -i "%%F"
)
echo Success
pause