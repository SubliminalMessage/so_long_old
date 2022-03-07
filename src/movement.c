/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:21:22 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/07 14:24:34 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

// Moves player in 'dir' direction.
// dir == w -> Up
// dir == d -> Right
// dir == s -> Down
// dir == a -> Left
void	player_move(char dir, t_map *map)
{
	int	new_pos;
	int	i;
	int	j;

	map->next_move = (map->next_move + 1) % 13 % 4;
	new_pos = map->p_pos;
	if (dir == 'w')
		new_pos -= map->width;
	if (dir == 'd')
		new_pos += 1;
	if (dir == 's')
		new_pos += map->width;
	if (dir == 'a')
		new_pos -= 1;
	i = new_pos / map->width;
	j = new_pos % map->width;
	if (map->at[i][j] == '1')
		return ;
	check_event_triggers(new_pos, map);
	move_enemies(map);
	check_event_triggers(new_pos, map);
	print_at(map->p_pos, map, 0);
	map->p_pos = new_pos;
	print_entities(map);
	print_current_moves(map);
}

// Checks if the game should end (either by winning or by losing)
void	check_event_triggers(int pos, t_map *map)
{
	int	i;
	int	j;
	int	k;

	i = pos / map->width;
	j = pos % map->width;
	if (map->at[i][j] == 'e')
		clean_exit("Congrats! You've won!\n", map);
	k = -1;
	while (++k < map->c_enemies)
	{
		if (map->p_enemy[k] == pos)
			clean_exit("Oops.. You lost\n", map);
	}
	if (map->at[i][j] == 'C')
	{
		map->at[i][j] = 'c';
		map->c_buttons--;
		if (map->c_buttons <= 0)
			open_all_doors(map);
	}
}

// Opens every map exit door, once you've pressed every button
void	open_all_doors(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->heigth)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->at[i][j] == 'E')
			{
				map->at[i][j] = 'e';
				print_at(i * map->width + j, map, 0);
			}
		}
	}
}

// Prints on screen current nº of moves
void	print_current_moves(t_map *map)
{
	static int	moves = -1;
	char		*text;
	char		*itoa;
	int			i;

	moves++;
	itoa = ft_itoa(moves);
	text = ft_strjoin("Movements: ", itoa);
	i = -1;
	while (++i < map->width)
		print_img(map, 0, i * 42, map->heigth * 42);
	i = 0xFFFFFFFF;
	mlx_string_put(map->mlx, map->win, 21, map->heigth * 42 + 21, i, text);
	free(itoa);
	free(text);
	(void) map;
}

// Moves every enemy (if any) in a 'circular' motion
void	move_enemies(t_map *map)
{
	int		i;
	int		j;
	int		k;

	k = -1;
	while (++k < map->c_enemies)
	{
		i = map->p_enemy[k] / map->width;
		j = map->p_enemy[k] % map->width;
		print_img(map, 5, j * 42, i * 42);
		if (map->next_move == 0 && map->at[i - 1][j] == '0')
			map->p_enemy[k] = (i - 1) * map->width + j;
		if (map->next_move == 1 && map->at[i][j + 1] == '0')
			map->p_enemy[k] = i * map->width + j + 1;
		if (map->next_move == 2 && map->at[i + 1][j] == '0')
			map->p_enemy[k] = (i + 1) * map->width + j;
		if (map->next_move == 3 && map->at[i][j - 1] == '0')
			map->p_enemy[k] = i * map->width + j - 1;
	}
}
