#include "goodness.hpp"
#include <algorithm>
#include <iostream>

GoodnessLevel goodnessAmountLevel(int32_t goodnessAmount)
{
    if(goodnessAmount < 25)
        return GoodnessLevel::Evil;
    else if(goodnessAmount < 50)
        return GoodnessLevel::Dying;
    else if(goodnessAmount < 75)
        return GoodnessLevel::Corrupt;
    else
        return GoodnessLevel::Good;
}

int32_t goodnessLevelAmount(GoodnessLevel level, int32_t goodnessAmount)
{
    int32_t base = 0;
    bool invert = false;

    if(level == GoodnessLevel::Evil)
    {
        base = 0;
        invert = true;
    }
    else if(level == GoodnessLevel::Dying)
    {
        base = 25;
        invert = true;
    }
    else if(level == GoodnessLevel::Corrupt)
    {
        base = 50;
        invert = true;
    }
    else if(level == GoodnessLevel::Good)
    {
        base = 75;
        invert = false;
    }

    int32_t toReturn;
    if(invert)
        toReturn = std::max(0, 100 + (base - goodnessAmount) * 4);
    else
        toReturn = std::max(0, (goodnessAmount - base) * 4);

    if(toReturn > 100)
    {
        toReturn -= 130;
        toReturn = std::max(0, 8 - toReturn);
    }

    return toReturn;
}
