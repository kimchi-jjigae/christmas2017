#pragma once
#include <cstdint>

enum GoodnessLevel { Evil, Dying, Corrupt, Good };

GoodnessLevel goodnessAmountLevel(int32_t goodnessAmount);
int32_t goodnessLevelAmount(GoodnessLevel level, int32_t goodnessAmount);
