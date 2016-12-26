#include "collisionlogic.hpp"
#include "aabbutil.hpp"

CollisionLogic::CollisionLogic(GameData& data):
    mData(data)
{
}

void CollisionLogic::update()
{
    for(size_t colAIter = 0; colAIter < mData.tEntityCollider.ids.size(); ++colAIter)
    {
        int32_t colAId = mData.tEntityCollider.ids[colAIter];
        const EntityCollider& colliderA = get(colAId, mData.tEntityCollider);
        const AABB& hitboxA = get(colAId, mData.tHitbox).aabb;
        const Position& positionA = get(colAId, mData.tPosition);

        AABB hitboxAWorld
        {
            hitboxA.start + positionA.coordinate,
            hitboxA.size + positionA.coordinate,
        };

        for(size_t colBIter = colAIter + 1; colBIter < mData.tEntityCollider.ids.size(); ++colBIter)
        {
            int32_t colBId = mData.tEntityCollider.ids[colBIter];
            const EntityCollider& colliderB = get(colBId, mData.tEntityCollider);
            const AABB& hitboxB = get(colBId, mData.tHitbox).aabb;
            const Position& positionB = get(colBId, mData.tPosition);

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
