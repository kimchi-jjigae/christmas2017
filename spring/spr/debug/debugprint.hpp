#pragma once
#include <iostream>
#include <cstdint>

//debug code blocks
#ifdef DEBUG_ON
#define Debug() if(true)
#define DebugF(x) if(dbg::getFlag(x))
#else
#define Debug() if(false)
#define DebugF(x) if(false)
#endif

//debug prints
#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0 (EVAL0 (EVAL0 (__VA_ARGS__)))
#define EVAL2(...) EVAL1 (EVAL1 (EVAL1 (__VA_ARGS__)))
#define EVAL3(...) EVAL2 (EVAL2 (EVAL2 (__VA_ARGS__)))
#define EVAL4(...) EVAL3 (EVAL3 (EVAL3 (__VA_ARGS__)))
#define EVAL(...)  EVAL4 (EVAL4 (EVAL4 (__VA_ARGS__)))

#define MAP_END(...)
#define MAP_OUT

#define MAP_GET_END() 0, MAP_END
#define MAP_NEXT0(test, next, ...) next MAP_OUT
#define MAP_NEXT1(test, next) MAP_NEXT0 (test, next, 0)
#define MAP_NEXT(test, next)  MAP_NEXT1 (MAP_GET_END test, next)

#define MAP0(f, x, peek, ...) f(x) MAP_NEXT (peek, MAP1) (f, peek, __VA_ARGS__)
#define MAP1(f, x, peek, ...) f(x) MAP_NEXT (peek, MAP0) (f, peek, __VA_ARGS__)
#define MAP(f, ...) EVAL (MAP1 (f, __VA_ARGS__, (), 0))


#ifdef DEBUG_ON
#define PRINT_WITH_NAME(x) \
    std::cout << #x": " << x << ", ";

#define dbgPrintV(...) \
    MAP(PRINT_WITH_NAME, __VA_ARGS__) \
    std::cout << "\n";

#define dbgPrint(text) \
    std::cout << text << "\n";
#else
#define PRINT_WITH_NAME(x)
#define dbgPrintV(...)
#define dbgPrint(text)
#endif
