#pragma once
#include <spr/data/tables.hpp>

namespace spr
{
class CollisionLogic
{
    public:
        CollisionLogic(Tables& tables);
        void update();
    private:
        Tables& mTables;
};
}
