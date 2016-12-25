#include "collisionlogic.hpp"
#include "aabbutil.hpp"

CollisionLogic::CollisionLogic(GameData& data):
    mData(data)
{
}

void CollisionLogic::update()
{
    for(int32_t colAId = 0; colAId < static_cast<int32_t>(mData.tEntityCollider.ids.size()); ++colAId)
    {
        for(int32_t colBId = colAId + 1; colBId < static_cast<int32_t>(mData.tEntityCollider.ids.size()); ++colBId)
        {
            const EntityCollider& colliderA = get(colAId, mData.tEntityCollider);
            const EntityCollider& colliderB = get(colBId, mData.tEntityCollider);
            const AABB& hitboxA = get(colAId, mData.tHitbox).aabb;
            const AABB& hitboxB = get(colBId, mData.tHitbox).aabb;
            const Position& positionA = get(colAId, mData.tPosition);
            const Position& positionB = get(colBId, mData.tPosition);

            AABB hitboxAWorld
            {
                hitboxA.start + positionA.coordinate,
                hitboxA.size + positionA.coordinate,
            };
            AABB hitboxBWorld
            {
                hitboxB.start + positionB.coordinate,
                hitboxB.size + positionB.coordinate,
            };

            if(intersects(hitboxAWorld, hitboxBWorld))
            {
                //call callback
                //
                //base on trigger
            }
        }
    }
}
