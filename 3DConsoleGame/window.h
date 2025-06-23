#pragma once

#include "map.h"
#include "player.h"
#include <Windows.h>
#include <string>

namespace game
{
    class GameWindow
    {
    public:
        GameWindow(std::int16_t width, std::int16_t height);
        GameWindow(GameWindow& other);
        GameWindow(GameWindow&&) = default;

        auto operator=(GameWindow&) -> GameWindow& = delete;
        auto operator=(GameWindow&&) -> GameWindow& = default;

        auto attach_map(Map& map) -> void;
        auto attach_player(Player& player) -> void;
        auto mainloop() -> void;

        auto get_screen_buffer() -> std::wstring&;
        auto draw_buffer() -> void;

        std::int16_t width_;
        std::int16_t height_;
        Map map_;
        Player player_;

    private:
        HANDLE console_;
        DWORD bytes_written_;
        std::wstring screen_buffer_;

        friend class Render;
    };
}
