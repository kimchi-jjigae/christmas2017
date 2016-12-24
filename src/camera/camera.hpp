#pragma once
#include <glm.hpp>
#include <thero/optional.hpp>

struct Camera
{
    glm::ivec2 position;
    float zoom = 1.0f;
    th::Optional<int32_t> cameraEntity;
};
