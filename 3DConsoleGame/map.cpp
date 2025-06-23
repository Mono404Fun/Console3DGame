#include "map.h"

namespace game
{
	Map::Map(std::wstring map, std::int16_t width, std::int16_t height)
		: map_(std::move(map)), width_(width), height_(height) {}

	Map::Map(const Map& other)
		: map_(other.map_), width_(other.width_), height_(other.height_) {}

    Map::Map(Map&& other) noexcept
    : map_(std::move(other.map_)), width_(other.width_), height_(other.height_)
    {
        other.width_ = 0;
        other.height_ = 0;
    }

	auto Map::operator=(const Map& other) -> Map&
	{
		if (this != &other)
		{
			map_ = other.map_;
			width_ = other.width_;
			height_ = other.height_;
		}
		return *this;
	}
    
    auto Map::operator=(Map&& other) noexcept -> Map&
    {
        if (this != &other)
        {
            map_ = std::move(other.map_);
            width_ = other.width_;
            height_ = other.height_;
            other.width_ = 0;
            other.height_ = 0;
        }
        return *this;
    }
    
	auto Map::getMap() const -> const std::wstring& { return map_; }
	auto Map::getWidth() const -> std::int16_t { return width_; }
	auto Map::getHeight() const -> std::int16_t { return height_; }
}
