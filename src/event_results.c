#include <so_long.h>

// Everytime you press a key, this function handles it
// ESC: 53
//  W: 13
//  A: 0
//  S: 1
//  D: 2
int	handle_key(int key, t_map *map)
{
	if (key == 13)
		player_move('w', map);
	if (key == 0)
		player_move('a', map);
	if (key == 1)
		player_move('s', map);
	if (key == 2)
		player_move('d', map);
	if (key == 53)
		clean_exit(NULL, map);
	return (0);
}

// Exits the program. Used when you close the window.
// Return value useless, just to mute 'unused variable' warnings
int	window_close(int idk, t_map *map)
{
	exit(0);
	return (map->c_buttons + idk);
}