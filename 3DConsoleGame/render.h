#pragma once

#include "window.h"

namespace game
{
	class Render
	{
	public:
		explicit Render(GameWindow& game_window);

		auto drawScene(const float delta_time) -> void;
		auto printStats(const float delta_time) -> void;

	private:
		GameWindow& game_window_;
		float distance_to_wall;
		bool hit_wall = false;
		bool boundary = false;
	};
}
