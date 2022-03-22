/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:21:22 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/22 17:54:42 by dangonza         ###   ########.fr       */
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

	moves++;
	if (moves != 0)
		printf("Movements: %d\n", moves);
	(void) map;
}
