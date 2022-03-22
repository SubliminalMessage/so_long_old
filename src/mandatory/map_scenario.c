/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_scenario.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:20:00 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/22 17:45:59 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

// Prints the background of the image
// It also calls the rest of print_something() functions
void	print_background(t_map *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->width)
	{
		j = 0;
		while (j < m->heigth + 1)
		{
			print_img(m, 0, i * 42, j * 42);
			j++;
		}
		i++;
	}
	print_borders(m);
	print_scenario(m);
	m->at[m->p_pos / m->width][m->p_pos % m->width] = '0';
	i = -1;
	print_entities(m);
}

// Prints every entity on the map. It's also used in animations
void	print_entities(t_map *map)
{
	int	i;
	int	j;

	i = map->p_pos / map->width;
	j = map->p_pos % map->width;
	print_img(map, 5, j * 42, i * 42);
	if (map->at[i][j] == 'E')
		print_img(map, 13, j * 42, i * 42);
	if (map->at[i][j] == 'C' || map->at[i][j] == 'c')
		print_img(map, 11, j * 42, i * 42);
	print_img(map, 15 + (map->next_frame % 2), j * 42, i * 42);
}

// Prints the map borders
void	print_borders(t_map *map)
{
	int	i;

	i = 0;
	while (++i < map->width - 1)
	{
		print_img(map, 2, i * 42, 0);
		print_img(map, 8, i * 42, (map->heigth - 1) * 42);
	}
	i = 0;
	while (++i < map->heigth - 1)
	{
		print_img(map, 4, 0, i * 42);
		print_img(map, 6, (map->width - 1) * 42, i * 42);
	}
	print_img(map, 1, 0, 0);
	print_img(map, 3, (map->width - 1) * 42, 0);
	print_img(map, 7, 0, (map->heigth - 1) * 42);
	print_img(map, 9, (map->width - 1) * 42, (map->heigth - 1) * 42);
}

// Prints the inner-map stuff. (Tiles, rocks, collectibles and exits)
void	print_scenario(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (++i < (map->heigth - 1))
	{
		j = 0;
		while (++j < (map->width - 1))
		{
			print_img(map, 5, j * 42, i * 42);
			if (map->at[i][j] == '1')
				print_img(map, 10, j * 42, i * 42);
			if (map->at[i][j] == 'E')
				print_img(map, 13, j * 42, i * 42);
			if (map->at[i][j] == 'C')
				print_img(map, 11, j * 42, i * 42);
		}
	}
}

// id == 0 => Auto
// id == 1 => Player
// id == 2 => Enemy
// Prints a single sprite on a given position. Used in animations
void	print_at(int position, t_map *map, int id)
{
	int	i;
	int	j;

	i = position / map->width;
	j = position % map->width;
	if (id == 1)
		print_img(map, 15 + map->next_frame % 2, j * 42, i * 42);
	if (id == 2)
		print_img(map, 17 + map->next_frame % 4, j * 42, i * 42);
	if (id == 0)
	{
		print_img(map, 5, j * 42, i * 42);
		if (map->at[i][j] == 'C')
			print_img(map, 11, j * 42, i * 42);
		if (map->at[i][j] == 'c')
			print_img(map, 12, j * 42, i * 42);
		if (map->at[i][j] == 'E')
			print_img(map, 13, j * 42, i * 42);
		if (map->at[i][j] == 'e')
			print_img(map, 14, j * 42, i * 42);
	}
}
