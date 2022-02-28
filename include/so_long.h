#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>

typedef struct  s_map
{
    int m_width;
    int m_heigth;
    int n_players;
    int n_enemies;
    int n_collectibles;
    int n_collects_picked;
    int n_obstacles;
    int n_exits;
    int player_pos;
    int *enemies;
    int *obstacles;
    int *collectibles;
    int *colls_picked;
    int *exits;
}   t_map;

void	clean_exit(char *error, t_map *map);
t_map   *init_map(void);
t_map   *parse_map(char *file_path);
void    map_info_from_line(char *line, t_map *map);
void	is_valid_map_line(char *line, int l_len, t_map *map);
void    get_map_positions(char *file_path, t_map *map);
void    get_positions_from_line(char *line, t_map *map, int line_number);

#endif