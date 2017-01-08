#pragma once
#include <vector>
#include <spr/tables/tablemodule.hpp>

namespace spr
{
class EntityStatesLogic
{
    public:
        EntityStatesLogic(TableModule& tables);
        std::vector<int32_t> update();
    private:
        TableModule& mTables;
};
}
