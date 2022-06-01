/************************************************\
 * VeritaSTG: Resource.hpp                      *
 * Resources utility classes.                   *
 *                                              *
 * Licensed under the MIT license.              *
\************************************************/

#pragma once

#include <optional>
#include <string>

#include "engine_panic.hpp"

namespace VeritaSTG {
    template <typename T>
    struct ResourceResult {
        T resource;
        int result;
    };

    // Used for file-based resources, which are most of them.
    // (the only exception I could think of are images, loaded from textures)
    template <typename T>
    class LazyResource {
        std::string path;
        std::optional<T> resource;
    public:
        inline LazyResource(void) {}
        inline LazyResource(std::string path) { this->path = path; }
        inline std::string GetPath(void) { return path; }
        inline bool Initialized(void) { return resource.has_value(); }
        inline void Initialize(T resource) { this->resource = resource; }
        inline T& Unwrap(void) {
            if (!Initialized()) // Needs to be like this because the function must return...
                EnginePanic("Tried to unwrap an uninitialized LazyResource");
            return resource.value();
        }
    };

    // Same as above but the resource is a nullable reference instead
    template <typename T>
    class LazyResourceReference {
        std::string path;
        T* resource = nullptr;
    public:
        inline LazyResourceReference(void) {}
        inline LazyResourceReference(std::string path) { this->path = path; }
        inline ~LazyResourceReference() { if (resource != nullptr) delete resource; }
        inline std::string GetPath(void) { return path; }
        inline bool Initialized(void) { return resource != nullptr; }
        inline void Initialize(T* resource) { this->resource = resource; }
        inline T* Unwrap(void) {
            if (!Initialized()) // Needs to be like this because the function must return...
                EnginePanic("Tried to unwrap an uninitialized LazyResourceReference");
            return resource;
        }
    };
}
