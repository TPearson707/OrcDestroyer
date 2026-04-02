#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

template <typename Resource, typename Identifier>
class ResourceManager {
    public:
        void load(Identifier id, const std::string& filename);
        template <typename Parameter>
        void load (Identifier id, const std::string& filename, Parameter secondParam);

        Resource& get(Identifier id);
        const Resource& get(Identifier id) const;

    private:
        std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
};

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename) {
    std::unique_ptr<Resource> resource(new Resource());

    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("ResourceManager::load - Failed to load " + filename);
    }

    auto inserted = resourceMap.emplace(id, std::move(resource));
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::load(Identifier id, const std::string& filename, Parameter secondParam) {
    std::unique_ptr<Resource> resource(new Resource());

    if (!resource->loadFromFile(filename, secondParam))
        throw std::runtime_error("ResourceManager::load - Failed to load " + filename);

    auto inserted = resourceMap.emplace(id, std::move(resource));
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id) {
    auto found = resourceMap.find(id);
    assert(found != resourceMap.end());
    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const {
    auto found = resourceMap.find(id);
    assert(found != resourceMap.end());
    return *found->second;
}