#include "player.h"
#include "config.h"

namespace game
{
    PlayerCoordinates::PlayerCoordinates(float x, float y, float angle, float fov, float depth)
        : x_(x), y_(y), angle_(angle), fov_(fov), depth_(depth), look_offset_(0.0f) {}

    PlayerCoordinates::PlayerCoordinates(const PlayerCoordinates& other)
        : x_(other.x_), y_(other.y_), angle_(other.angle_), fov_(other.fov_), depth_(other.depth_), look_offset_(other.look_offset_) {}

    PlayerCoordinates::PlayerCoordinates(PlayerCoordinates&& other) noexcept
        : x_(other.x_), y_(other.y_), angle_(other.angle_), fov_(other.fov_), depth_(other.depth_), look_offset_(other.look_offset_) {}

    auto PlayerCoordinates::operator=(const PlayerCoordinates& other) -> PlayerCoordinates&
    {
        if (this != &other)
        {
            x_ = other.x_;
            y_ = other.y_;
            angle_ = other.angle_;
            fov_ = other.fov_;
            depth_ = other.depth_;
            look_offset_ = other.look_offset_;
        }
        return *this;
    }

    auto PlayerCoordinates::operator=(PlayerCoordinates&& other) noexcept -> PlayerCoordinates&
    {
        if (this != &other)
        {
            x_ = other.x_;
            y_ = other.y_;
            angle_ = other.angle_;
            fov_ = other.fov_;
            depth_ = other.depth_;
            look_offset_ = other.look_offset_;
        }
        return *this;
    }

    Player::Player(const PlayerCoordinates& player_coordinates, const Map& map)
    : player_coordinates_(player_coordinates), map_(map) {}

    Player::Player(const Player& other)
    : player_coordinates_(other.player_coordinates_), map_(other.map_) {}

    Player::Player(Player&& other) noexcept
        : player_coordinates_(std::move(other.player_coordinates_)),
        map_(std::move(other.map_)) {}

        auto Player::operator=(const Player& other) -> Player&
        {
            if (this != &other)
            {
                player_coordinates_ = other.player_coordinates_;
                map_ = other.map_;
            }
            return *this;
        }

        auto Player::operator=(Player&& other) noexcept -> Player&
        {
            if (this != &other)
            {
                player_coordinates_ = std::move(other.player_coordinates_);
                map_ = std::move(other.map_);
            }
        return *this;
    }

    static inline bool is_colliding(float x, float y, const Map& map)
    {
        auto ix = static_cast<int>(x);
        auto iy = static_cast<int>(y);
        return map.getMap()[iy * map.getWidth() + ix] == L'#';
    }

    auto Player::moveForward(float delta_time) -> void
    {
        const float move_speed = DEFAULT_MOVEMENT_SPEED;
        float new_x = player_coordinates_.x_ + sinf(player_coordinates_.angle_) * move_speed * delta_time;
        float new_y = player_coordinates_.y_ + cosf(player_coordinates_.angle_) * move_speed * delta_time;

        if (!is_colliding(new_x, new_y, map_))
        {
            player_coordinates_.x_ = new_x;
            player_coordinates_.y_ = new_y;
        }
    }

    auto Player::moveBackward(float delta_time) -> void
    {
        const float move_speed = DEFAULT_MOVEMENT_SPEED;
        float new_x = player_coordinates_.x_ - sinf(player_coordinates_.angle_) * move_speed * delta_time;
        float new_y = player_coordinates_.y_ - cosf(player_coordinates_.angle_) * move_speed * delta_time;

        if (!is_colliding(new_x, new_y, map_))
        {
            player_coordinates_.x_ = new_x;
            player_coordinates_.y_ = new_y;
        }
    }

    auto Player::moveLeft(float delta_time) -> void
    {
        const float move_speed = DEFAULT_MOVEMENT_SPEED;
        float new_x = player_coordinates_.x_ - cosf(player_coordinates_.angle_) * move_speed * delta_time;
        float new_y = player_coordinates_.y_ + sinf(player_coordinates_.angle_) * move_speed * delta_time;

        if (!is_colliding(new_x, new_y, map_))
        {
            player_coordinates_.x_ = new_x;
            player_coordinates_.y_ = new_y;
        }
    }

    auto Player::moveRight(float delta_time) -> void
    {
        const float move_speed = DEFAULT_MOVEMENT_SPEED;
        float new_x = player_coordinates_.x_ + cosf(player_coordinates_.angle_) * move_speed * delta_time;
        float new_y = player_coordinates_.y_ - sinf(player_coordinates_.angle_) * move_speed * delta_time;

        if (!is_colliding(new_x, new_y, map_))
        {
            player_coordinates_.x_ = new_x;
            player_coordinates_.y_ = new_y;
        }
    }

    auto Player::rotateRight(float delta_time) -> void
    {
        player_coordinates_.angle_ += DEFAULT_ROTATION_SPEED * delta_time;
    }

    auto Player::rotateLeft(float delta_time) -> void
    {
        player_coordinates_.angle_ -= DEFAULT_ROTATION_SPEED * delta_time;
    }
}
