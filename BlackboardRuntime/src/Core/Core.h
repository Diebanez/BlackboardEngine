//
// Created by diego on 24/07/2020.
//

#pragma once

#ifndef BLACKBOARDENGINE_CORE_H
#define BLACKBOARDENGINE_CORE_H

#ifdef BB_ENABLE_ASSERTS
    #define BB_CORE_ASSERT(x, ...) { if(!(x)) { BB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
    #define BB_ASSERT(x, ...) {if(!(x)) { BB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
    #define BB_CORE_ASSERT(x, ...)
    #define BB_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

#endif //BLACKBOARDENGINE_CORE_H
