#pragma once

#include "player.h"
#include "window.h"

namespace game
{
	class GameWindow;

	class Input
	{
	public:
		explicit Input(Player& player, GameWindow& game_window) noexcept;

		auto handleInput() -> void;
	private:
		Player& player_;
		GameWindow& game_window_;
	};
}
