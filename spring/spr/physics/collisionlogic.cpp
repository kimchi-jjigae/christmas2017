#include "collisionlogic.hpp"
#include "aabbutil.hpp"
#include <spr/debug/debug.hpp>
#include <spr/data/entitycollider.hpp>
#include <spr/data/hitbox.hpp>
#include <spr/data/position.hpp>

namespace spr
{
CollisionLogic::CollisionLogic(Tables& tables):
    mTables(tables)
{
}

void CollisionLogic::update()
{
    for(size_t colAIter = 0; colAIter < static_cast<size_t>(count(*mTables.tEntityCollider)); ++colAIter)
    {
        int32_t colAId = mTables.tEntityCollider->ids[colAIter];
        const EntityCollider& colliderA = get(colAId, *mTables.tEntityCollider);
        const AABB& hitboxA = get(colAId, *mTables.tHitbox).aabb;
        const Position& positionA = get(colAId, *mTables.tPosition);

        AABB hitboxAWorld
        {
            hitboxA.start + positionA.coordinate,
            hitboxA.size,
        };

        spr::DRen::out << spr::DFrame{hitboxAWorld.start, hitboxAWorld.size, fea::Color::Yellow};

        for(size_t colBIter = colAIter + 1; colBIter < static_cast<size_t>(count(*mTables.tEntityCollider)); ++colBIter)
        {
            int32_t colBId = mTables.tEntityCollider->ids[colBIter];
            const EntityCollider& colliderB = get(colBId, *mTables.tEntityCollider);
            const AABB& hitboxB = get(colBId, *mTables.tHitbox).aabb;
            const Position& positionB = get(colBId, *mTables.tPosition);

            AABB hitboxBWorld
            {
                hitboxB.start + positionB.coordinate,
                hitboxB.size,
            };

            if(intersects(hitboxAWorld, hitboxBWorld))
            {
                //can use types like trigger/physics here to do stuff


                //A on B
                for(const auto& executor : colliderA.executors)
                {
                    CollisionContext context
                    {
                        colAId,
                        colBId,
                    };

                    executor.function(context);
                };

                //B on A
                for(const auto& executor : colliderB.executors)
                {
                    CollisionContext context
                    {
                        colBId,
                        colAId,
                    };

                    executor.function(context);
                };
            }
        }
    }
}
}
