#include "pch.h"

#include "ResourceSystem.h"

#include "Logger.h"

namespace XYZEngine {

ResourceSystem* ResourceSystem::Instance() {
    static ResourceSystem resourceSystem;
    return &resourceSystem;
}

void ResourceSystem::LoadTexture(const std::string& name,
                                 std::string sourcePath, bool isSmooth) {
    if (textures.find(name) != textures.end()) {
        return;
    }

    sf::Texture* newTexture = new sf::Texture();
    try {
        if (!newTexture->loadFromFile(sourcePath)) {
            throw std::invalid_argument("File not found: " + sourcePath + "\n");
        }
    } catch (const std::invalid_argument& e) {
        LOG_ERROR(e.what());
        newTexture->loadFromFile(
            "../XYZEngine/BaseResource/DefaultResource.png");
        newTexture->setSmooth(isSmooth);
        textures.emplace(name, newTexture);
    }

    newTexture->loadFromFile(sourcePath);
    newTexture->setSmooth(isSmooth);
    textures.emplace(name, newTexture);
}
const sf::Texture* ResourceSystem::GetTextureShared(
    const std::string& name) const {
    LOG_INFO("GetTextureShared: " +
             std::to_string(textures.find(name)->first == name) + "\n");
    return textures.find(name)->second;
}
sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const {
    return new sf::Texture(*textures.find(name)->second);
}
void ResourceSystem::DeleteSharedTexture(const std::string& name) {
    auto texturePair = textures.find(name);

    sf::Texture* deletingTexure = texturePair->second;
    textures.erase(texturePair);
    delete deletingTexure;
}

void ResourceSystem::LoadTextureMap(const std::string& name,
                                    std::string sourcePath,
                                    sf::Vector2u elementPixelSize,
                                    int totalElements, bool isSmooth) {
    if (textureMaps.find(name) != textureMaps.end()) {
        return;
    }

    sf::Texture textureMap;

    try {
        if (!textureMap.loadFromFile(sourcePath)) {
            throw std::invalid_argument("File not found: " + sourcePath + "\n");
        };
    } catch (const std::invalid_argument& e) {
        LOG_ERROR(e.what());
        textureMap.loadFromFile(
            "../XYZEngine/BaseResource/DefaulthMapResource.png");
        auto textureMapElements = new std::vector<sf::Texture*>();

        auto textureSize = textureMap.getSize();
        int loadedElements = 0;

        for (int y = 0; y <= textureSize.y - elementPixelSize.y;
             y += elementPixelSize.y) {
            if (loadedElements == totalElements) {
                break;
            }

            for (int x = 0; x <= textureSize.x - elementPixelSize.x;
                 x += elementPixelSize.x) {
                if (loadedElements == totalElements) {
                    break;
                }

                sf::Texture* newTextureMapElement = new sf::Texture();
                if (newTextureMapElement->loadFromFile(
                        "../XYZEngine/BaseResource/DefaulthMapResource.png",
                        sf::IntRect(x, y, elementPixelSize.x,
                                    elementPixelSize.y))) {
                    newTextureMapElement->setSmooth(isSmooth);
                    textureMapElements->push_back(newTextureMapElement);
                }
                loadedElements++;
            }
        }

        textureMaps.emplace(name, *textureMapElements);
    }
    textureMap.loadFromFile(sourcePath);
    auto textureMapElements = new std::vector<sf::Texture*>();

    auto textureSize = textureMap.getSize();
    int loadedElements = 0;

    for (int y = 0; y <= textureSize.y - elementPixelSize.y;
         y += elementPixelSize.y) {
        if (loadedElements == totalElements) {
            break;
        }

        for (int x = 0; x <= textureSize.x - elementPixelSize.x;
             x += elementPixelSize.x) {
            if (loadedElements == totalElements) {
                break;
            }

            sf::Texture* newTextureMapElement = new sf::Texture();
            if (newTextureMapElement->loadFromFile(
                    sourcePath, sf::IntRect(x, y, elementPixelSize.x,
                                            elementPixelSize.y))) {
                newTextureMapElement->setSmooth(isSmooth);
                textureMapElements->push_back(newTextureMapElement);
            }
            loadedElements++;
        }
    }

    textureMaps.emplace(name, *textureMapElements);
}
const sf::Texture* ResourceSystem::GetTextureMapElementShared(
    const std::string& name, int elementIndex) const {
    auto textureMap = textureMaps.find(name);
    auto textures = textureMap->second;
    return textures[elementIndex];
}
sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name,
                                                      int elementIndex) const {
    auto textureMap = textureMaps.find(name);
    auto textures = textureMap->second;
    return new sf::Texture(*textures[elementIndex]);
}
int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const {
    auto textureMap = textureMaps.find(name);
    auto textures = textureMap->second;
    return textures.size();
}
void ResourceSystem::DeleteSharedTextureMap(const std::string& name) {
    auto textureMap = textureMaps.find(name);
    auto deletingTextures = textureMap->second;

    for (int i = 0; i < deletingTextures.size(); i++) {
        delete deletingTextures[i];
    }

    textureMaps.erase(textureMap);
}

void ResourceSystem::Clear() {
    DeleteAllTextures();
    DeleteAllTextureMaps();
}

void ResourceSystem::DeleteAllTextures() {
    std::vector<std::string> keysToDelete;

    for (const auto& texturePair : textures) {
        keysToDelete.push_back(texturePair.first);
    }

    for (const auto& key : keysToDelete) {
        DeleteSharedTexture(key);
    }
}
void ResourceSystem::DeleteAllTextureMaps() {
    std::vector<std::string> keysToDelete;

    for (const auto& textureMapPair : textureMaps) {
        keysToDelete.push_back(textureMapPair.first);
    }

    for (const auto& key : keysToDelete) {
        DeleteSharedTextureMap(key);
    }
}

void ResourceSystem::LoadSound(const std::string& name,
                               std::string sourcePath) {
    if (sounds.find(name) != sounds.end()) {
        return;
    }

    sf::SoundBuffer* newSound = new sf::SoundBuffer();

    try {
        if (newSound->loadFromFile(sourcePath)) {
            throw std::invalid_argument("File not found: " + sourcePath + "\n");
        }
    } catch (const std::invalid_argument& e) {
        LOG_ERROR(e.what());
        newSound->loadFromFile("../XYZEngine/BaseResource/DefaultSound.wav");
        sounds.emplace(name, newSound);
    }

    newSound->loadFromFile(sourcePath);
    sounds.emplace(name, newSound);
}

const sf::SoundBuffer* ResourceSystem::GetSound(const std::string& name) const {
    return sounds.find(name)->second;
}

void ResourceSystem::DeleteSound(const std::string& name) {
    auto soundPair = sounds.find(name);

    sf::SoundBuffer* deletingSound = soundPair->second;
    sounds.erase(soundPair);
    delete deletingSound;
}
}  // namespace XYZEngine