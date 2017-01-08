#pragma once
#include <spr/tables/tablemodule.hpp>

namespace spr
{
class CollisionLogic
{
    public:
        CollisionLogic(TableModule& tables);
        void update();
    private:
        TableModule& mTables;
};
}
