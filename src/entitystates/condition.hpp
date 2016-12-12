#pragma once
#include <cstdint>
#include <string>

struct Condition
{
    enum Type { OnStateStart, OnStateEnd, EveryNthFrame, FrameRandomChance, FrameRange };
    Type type;

    static constexpr int32_t unbound = -1;

    union
    {
        struct
        {
            int32_t interval;
            int32_t offset;
        } everyNthFrame;

        struct
        {
            int32_t numerator;
            int32_t denominator;
        } frameRandomChance;

        struct
        {
            int32_t start;
            int32_t end;
        } frameRange;
    };
};

Condition onStateStart();
Condition onStateEnd();
Condition everyNthFrame(int32_t interval, int32_t offset);
Condition frameRandomChance(int32_t numerator, int32_t denominator);
Condition frameRange(int32_t start, int32_t end);

std::string toString(const Condition& condition);
