#include "render.h"
#include "config.h"
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

namespace game
{
    Render::Render(GameWindow& game_window) : game_window_(game_window) {}

    auto Render::drawScene(const float delta_time) -> void
    {
        const int screen_width = game_window_.width_;
        const int screen_height = game_window_.height_;

        auto& player_coords = game_window_.player_.player_coordinates_;
        float player_x = player_coords.x_;
        float player_y = player_coords.y_;
        float player_angle = player_coords.angle_;
        float fov = player_coords.fov_;
        float depth = player_coords.depth_;
        float look_offset = player_coords.look_offset_;

        const std::wstring& map = game_window_.player_.map_.getMap();
        int map_width = game_window_.player_.map_.getWidth();
        int map_height = game_window_.player_.map_.getHeight();

        for (int x = 0; x < screen_width; ++x)
        {
            float ray_angle = player_angle - fov / 2.0f + ((float)x / screen_width) * fov;
            float eye_x = sinf(ray_angle);
            float eye_y = cosf(ray_angle);

            float distance_to_wall = 0.0f;
            bool hit_wall = false;
            bool boundary = false;

            while (!hit_wall && distance_to_wall < depth)
            {
                distance_to_wall += 0.1f;
                int test_x = static_cast<int>(player_x + eye_x * distance_to_wall);
                int test_y = static_cast<int>(player_y + eye_y * distance_to_wall);

                if (test_x < 0 || test_x >= map_width || test_y < 0 || test_y >= map_height)
                {
                    hit_wall = true;
                    distance_to_wall = depth;
                }
                else if (map[test_y * map_width + test_x] == L'#')
                {
                    hit_wall = true;

                    std::vector<std::pair<float, float>> corners;
                    for (int tx = 0; tx < 2; ++tx)
                    {
                        for (int ty = 0; ty < 2; ++ty)
                        {
                            float vx = (float)test_x + tx - player_x;
                            float vy = (float)test_y + ty - player_y;
                            float d = sqrtf(vx * vx + vy * vy);
                            float dot = (eye_x * vx / d) + (eye_y * vy / d);
                            corners.emplace_back(d, dot);
                        }
                    }

                    std::sort(corners.begin(), corners.end(), [](auto& a, auto& b) {
                        return a.first < b.first;
                    });

                    float boundary_threshold = 0.01f;
                    if (acosf(corners[0].second) < boundary_threshold ||
                        acosf(corners[1].second) < boundary_threshold)
                    {
                        boundary = true;
                    }
                }
            }

            int ceiling = static_cast<int>(
                (screen_height / 2.0f) - screen_height / distance_to_wall
                - player_coords.look_pitch_ * (screen_height / 2.0f)
            );

            if (ceiling < 0) ceiling = 0;
            if (ceiling >= screen_height) ceiling = screen_height - 1;

            int floor = screen_height - ceiling;
            if (floor > screen_height) floor = screen_height;

            wchar_t wall_shade;
            if (distance_to_wall <= depth / 4.0f)
                wall_shade = 0x2588; // █
            else if (distance_to_wall < depth / 3.0f)
                wall_shade = 0x2593; // ▓
            else if (distance_to_wall < depth / 2.0f)
                wall_shade = 0x2592; // ▒
            else if (distance_to_wall < depth)
                wall_shade = 0x2591; // ░
            else
                wall_shade = ' ';

            if (boundary)
                wall_shade = ' ';

            for (int y = 0; y < screen_height; ++y)
            {
                if (y <= ceiling)
                {
                    game_window_.screen_buffer_[y * screen_width + x] = ' ';
                }
                else if (y > ceiling && y <= floor)
                {
                    game_window_.screen_buffer_[y * screen_width + x] = wall_shade;
                }
                else
                {
                    float brightness = 1.0f - ((float)(y - screen_height / 2) / (screen_height / 2));
                    wchar_t floor_shade;
                    if (brightness < 0.25f)
                        floor_shade = '.';
                    else if (brightness < 0.5f)
                        floor_shade = '-';
                    else if (brightness < 0.75f)
                        floor_shade = '=';
                    else if (brightness < 0.9f)
                        floor_shade = '+';
                    else
                        floor_shade = ' ';

                    game_window_.screen_buffer_[y * screen_width + x] = floor_shade;
                }
            }
        }

        swprintf_s(game_window_.screen_buffer_.data(), 80, L"X=%3.2f Y=%3.2f A=%3.2f FPS=%3.2f", game_window_.player_.player_coordinates_.x_, game_window_.player_.player_coordinates_.y_, game_window_.player_.player_coordinates_.angle_, 1.0f / delta_time);
        for (int nx = 0; nx < game_window_.map_.getWidth(); nx++)
            for (int ny = 0; ny < game_window_.map_.getWidth(); ny++)
                game_window_.screen_buffer_[(ny + 1) * game_window_.width_ + nx] = game_window_.map_.getMap()[ny * game_window_.map_.getWidth() + nx];

        game_window_.screen_buffer_[((int)game_window_.player_.player_coordinates_.y_ + 1) * game_window_.width_ + (int)game_window_.player_.player_coordinates_.x_] = 'P';
        game_window_.screen_buffer_[game_window_.width_ * game_window_.height_ - 1] = '\0';
        game_window_.draw_buffer();
    }
}
