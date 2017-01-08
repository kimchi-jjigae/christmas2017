#include <cstddef>
#include <iostream>
#include <spr/tables/tablemodule.hpp>

namespace spr
{
struct SprTablesCapacity
{
    size_t entitystatemachineCapacity;
    size_t entitystateCapacity;
    size_t entitystateindexCapacity;
    size_t entityorientationCapacity;
    size_t positionCapacity;
    size_t hitboxCapacity;
    size_t entitycolliderCapacity;
    size_t textureCapacity;
    size_t textureindexCapacity;
    size_t spriteanimationCapacity;
    size_t spriteanimationindexCapacity;
    size_t fourdirectionalanimationgroupCapacity;
    size_t fourdirectionalanimationgroupindexCapacity;
    size_t entityspriteinstanceCapacity;
    size_t spriteCapacity;
    size_t fourdirectionalspriteCapacity;
    size_t animatedspriteCapacity;
    size_t entitydirectionCapacity;
};

bool operator==(const SprTablesCapacity& a, const SprTablesCapacity& b);
bool operator!=(const SprTablesCapacity& a, const SprTablesCapacity& b);

SprTablesCapacity sprTablesCapacity(const spr::TableModule& tables);
void sprEnsureCapacity(size_t capacity, spr::TableModule& tables);

}
