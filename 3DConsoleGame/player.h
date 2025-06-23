#pragma once

#include "map.h"
#include <cmath>
#include <utility>

namespace game
{
    class Player;
    class Input;
    class Render;

    class PlayerCoordinates
    {
    public:
        PlayerCoordinates(float x, float y, float angle, float fov, float depth);
        PlayerCoordinates(const PlayerCoordinates& other);
        PlayerCoordinates(PlayerCoordinates&& other) noexcept;

        auto operator=(const PlayerCoordinates& other) -> PlayerCoordinates&;
        auto operator=(PlayerCoordinates&& other) noexcept -> PlayerCoordinates&;
    private:
        float x_{};
        float y_{};
        float angle_{};
        float fov_{};
        float depth_{};
        float look_offset_{};
        float look_pitch_{ 0.0f };

        friend class Player;
        friend class Render;
    };

    class Player
    {
    public:
        Player(const PlayerCoordinates& coordinates, const Map& map);
        Player(const Player& other);
        Player(Player&& other) noexcept;

        auto operator=(const Player& other) -> Player&;
        auto operator=(Player&& other) noexcept -> Player&;

        auto moveForward(float delta_time) -> void;
        auto moveBackward(float delta_time) -> void;
        auto moveLeft(float delta_time) -> void;
        auto moveRight(float delta_time) -> void;

        auto rotateRight(float delta_time) -> void;
        auto rotateLeft(float delta_time) -> void;

    private:
        PlayerCoordinates player_coordinates_;
        Map map_;

        friend class Render;
        friend class Input;
    };
}
