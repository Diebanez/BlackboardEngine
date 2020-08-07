//
// Created by diego on 24/07/2020.
//

#ifndef BLACKBOARDENGINE_CORE_H
#define BLACKBOARDENGINE_CORE_H

#include <memory>
#include "Log.h"

#ifdef BB_ENABLE_ASSERTS
    #define BB_CORE_ASSERT(x, ...) { if(!(x)) { BB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
    #define BB_ASSERT(x, ...) {if(!(x)) { BB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
    #define BB_CORE_ASSERT(x, ...)
    #define BB_ASSERT(x, ...)
#endif

#define BB_BIT(x) (1 << x)

namespace BlackboardRuntime{
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template <typename T, typename  ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args){
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    template<typename  T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args){
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif //BLACKBOARDENGINE_CORE_H
