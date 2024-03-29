/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:18:36 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/22 17:49:58 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdio.h>
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>

# define W_HEIGTH 2880
# define W_WIDTH 5120

typedef struct s_map {
	int		width;
	int		heigth;
	void	*mlx;
	void	*win;
	void	*imgs[21];
	int		c_buttons;
	int		c_enemies;
	int		p_pos;
	int		*p_enemy;
	char	**at;
	int		next_frame;
	int		next_move;
}	t_map;

void	clean_exit(char *msg, t_map *map);
t_map	*check_map_errors(char *path);
void	is_valid_map_line(char *line, int l_len, t_map *map);
void	check_errors_map_line(char *line, int data[5], t_map *map);
int		ft_line_len(char *line);
void	parse_map(t_map *map, char *path);
void	set_map_config(t_map *map);
void	set_pointers(t_map *map);
void	set_images(t_map *map);
void	*get_img(char *path, t_map *map);
void	print_img(t_map *map, int index, int x, int y);
void	print_background(t_map *map);
void	print_borders(t_map *map);
void	print_scenario(t_map *map, int e_idx);
void	player_move(char dir, t_map *map);
int		handle_key(int key, t_map *map);
int		window_close(int idk, t_map *map);
void	print_entities(t_map *map);
void	open_all_doors(t_map *map);
void	check_event_triggers(int pos, t_map *map);
void	print_current_moves(t_map *map);
int		animation_frames(t_map *map);
void	move_enemies(t_map *map);
void	check_parsed_map_errors(t_map *map);
void	print_at(int position, t_map *map, int id);
int		calc_next_enemy_move(t_map *map, int i, int j, int k);

#endif