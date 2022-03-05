#include <so_long.h>

// ESC: 53
//  W: 13
//  A: 0
//  S: 1
//  D: 2
int	handle_key(int key, t_map *map)
{
    //printf("Actual Pos: %d [%d][%d]\n", map->p_pos, map->p_pos / map->width, map->p_pos % map->width);
    //printf("Key press (%d)\n", key);
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

// Return value useless, just to mute 'unused variable' warnings
int	window_close(int idk, t_map *map)
{
	exit(0);
	return (map->c_buttons + idk);
}