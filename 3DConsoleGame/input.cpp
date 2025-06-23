#include "input.h"
#include "render.h"
#include "window.h"

#include <Windows.h>
#include <chrono>

namespace game
{
	Input::Input(Player& player, GameWindow& game_window) noexcept
		: player_(player), game_window_(game_window) {}

	auto Input::handleInput() -> void
	{
		auto tp1 = std::chrono::system_clock::now();
		auto tp2 = std::chrono::system_clock::now();

		while (true)
		{
			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsed = tp2 - tp1;
			tp1 = tp2;
			const float delta_time = elapsed.count();

			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
				player_.rotateLeft(delta_time);
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
				player_.rotateRight(delta_time);

			if (GetAsyncKeyState('Q') & 0x8000)
				player_.moveLeft(delta_time);
			if (GetAsyncKeyState('D') & 0x8000)
				player_.moveRight(delta_time);
			if (GetAsyncKeyState('Z') & 0x8000)
				player_.moveForward(delta_time);
			if (GetAsyncKeyState('S') & 0x8000)
				player_.moveBackward(delta_time);

			Render renderer(game_window_);
			renderer.drawScene(delta_time);
		}
	}
}
