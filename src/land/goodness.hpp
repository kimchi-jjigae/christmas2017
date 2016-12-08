#pragma once
#include <cstdint>

enum GoodnessLevel { Evil, Dying, Corrupt, Good };

int32_t goodnessLevelAmount(GoodnessLevel level, int32_t goodnessAmount);
