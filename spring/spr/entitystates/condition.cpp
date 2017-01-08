#include "condition.hpp"

namespace spr
{
Condition onStateStart()
{
    Condition result;
    result.type = Condition::OnStateStart;
    return result;
}

Condition onStateEnd()
{
    Condition result;
    result.type = Condition::OnStateEnd;
    return result;
}

Condition everyNthFrame(int32_t interval, int32_t offset)
{
    Condition result;
    result.type = Condition::EveryNthFrame;
    result.everyNthFrame.interval = interval;
    result.everyNthFrame.offset = offset;
    return result;
}

Condition frameRange(int32_t start, int32_t end)
{
    Condition result;
    result.type = Condition::FrameRange;
    result.frameRange.start = start;
    result.frameRange.end = end;
    return result;
}

std::string toString(const Condition& condition)
{
    if(condition.type == Condition::OnStateStart)
        return "OnStateStart";
    else if(condition.type == Condition::OnStateEnd)
        return "OnStateEnd";
    else if(condition.type == Condition::EveryNthFrame)
        return "EveryNthFrame";
    else if(condition.type == Condition::FrameRange)
        return "FrameRange";
    return "N/A";
}
}
