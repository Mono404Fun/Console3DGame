#pragma once

#include <string>
#include <cstdint>

namespace game
{
	class Player;

	class Map
	{
	public:
		Map(std::wstring map, std::int16_t width, std::int16_t height);

		Map(const Map& other);
		Map(Map&& other) noexcept;

		auto operator=(const Map& other) -> Map&;
		auto operator=(Map&& other) noexcept -> Map&;
		auto getMap() const -> const std::wstring&;
		auto getWidth() const -> std::int16_t;
		auto getHeight() const -> std::int16_t;

	private:
		std::wstring map_;
		std::int16_t width_;
		std::int16_t height_;

		friend class Player;
	};
}
