#include "window.h"
#include "config.h"

using namespace game;

int main()
{
    GameWindow game_window = GameWindow(120, 40);
    std::wstring map_ =
        L"################"
        L"#..............#"
        L"#############..#"
        L"#..............#"
        L"#...######..####"
        L"#..#######..####"
        L"#....####...#..#"
        L"#.##..#..#..#..#"
        L"#...........#..#"
        L"#....##...####.#"
        L"#..####........#"
        L"#....#####.....#"
        L"#..............#"
        L"#########......#"
        L"#..........##..#"
        L"################";

    Map map = Map(map_, DEFAULT_MAP_WIDTH, DEFAULT_MAP_HEIGHT);
    PlayerCoordinates player_coordinates = PlayerCoordinates(
        DEFAULT_X_POSITON,
        DEFAULT_Y_POSITON,
        DEFAULT_ANGLE,
        DEFAULT_FOV,
        DEFAULT_DEPTH);
    Player player = Player(player_coordinates, map);
    game_window.attach_map(map);
    game_window.attach_player(player);
    game_window.mainloop();
    return 0;
}
