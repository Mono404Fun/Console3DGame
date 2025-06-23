#include "window.h"
#include "input.h"
#include "config.h"

namespace game
{
    GameWindow::GameWindow(std::int16_t width, std::int16_t height)
        : width_(width),
          height_(height),
          map_(DEFAULT_MAP, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT),
          player_(PlayerCoordinates(DEFAULT_X_POSITON,
                                    DEFAULT_Y_POSITON,
                                    DEFAULT_ANGLE,
                                    DEFAULT_FOV,
                                    DEFAULT_DEPTH),
                  map_),
          screen_buffer_(width * height, L' '),
          bytes_written_(0)
    {
        console_ = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(console_);
    }

    GameWindow::GameWindow(GameWindow& other)
        : width_(other.width_),
          height_(other.height_),
          map_(other.map_),
          player_(other.player_),
          screen_buffer_(other.screen_buffer_),
          console_(other.console_),
          bytes_written_(other.bytes_written_) {}

    auto GameWindow::attach_map(Map& map) -> void
    {
        map_ = map;
    }

    auto GameWindow::attach_player(Player& player) -> void
    {
        player_ = player;
    }

    auto GameWindow::mainloop() -> void
    {
        Input input_handler(player_, *this);
        input_handler.handleInput();
    }

    auto GameWindow::get_screen_buffer() -> std::wstring&
    {
        return screen_buffer_;
    }

    auto GameWindow::draw_buffer() -> void
    {
        WriteConsoleOutputCharacterW(console_, screen_buffer_.data(), screen_buffer_.size(), {0, 0}, &bytes_written_);
    }
}
