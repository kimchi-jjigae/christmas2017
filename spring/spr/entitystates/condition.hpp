#pragma once
#include <cstdint>
#include <string>

namespace spr
{
struct Condition
{
    enum Type { OnStateStart, OnStateEnd, EveryNthFrame, FrameRange };
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
            int32_t start;
            int32_t end;
        } frameRange;
    };
};

Condition onStateStart();
Condition onStateEnd();
Condition everyNthFrame(int32_t interval, int32_t offset);
Condition frameRange(int32_t start, int32_t end);

std::string toString(const Condition& condition);
}
