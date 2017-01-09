#pragma once
#include <vector>
#include <spr/data/tables.hpp>

namespace spr
{
class EntityStatesLogic
{
    public:
        EntityStatesLogic(Tables& tables);
        std::vector<int32_t> update();
    private:
        Tables& mTables;
};
}
