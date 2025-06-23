#pragma once

#include <cstdint>
#include <string>

namespace game
{
    constexpr inline std::int16_t DEFAULT_SCREEN_WIDTH = 120;
    constexpr inline std::int16_t DEFAULT_SCREEN_HEIGHT = 40;
    constexpr inline float DEFAULT_X_POSITON = 1.0f;
    constexpr inline float DEFAULT_Y_POSITON = 1.0f;
    constexpr inline float DEFAULT_FOV = 3.14159f / 4.0f;
    constexpr inline float DEFAULT_ANGLE = DEFAULT_FOV / 2.0f;
    constexpr inline float DEFAULT_DEPTH = 16.0f;
    constexpr inline float DEFAULT_MOVEMENT_SPEED = 5.0f;
    constexpr inline float DEFAULT_ROTATION_SPEED = 2.5f;

    constexpr inline std::int16_t DEFAULT_MAP_WIDTH = 16;
    constexpr inline std::int16_t DEFAULT_MAP_HEIGHT = 16;

    inline const std::wstring DEFAULT_MAP = 
        L"################"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"#..............#"
        L"################";
}
