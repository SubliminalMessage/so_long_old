/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:23:02 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/03 18:55:15 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	clean_exit(char *msg, t_map *map)
{
	int	i;

	printf("%s\n", msg);
	if (map != NULL)
	{
		i = -1;
		if (map->at != NULL)
		{
			while (++i < map->heigth)
				free(map->at[i]);
			free(map->at);
		}
		free(map);
	}
	exit(0);
}

//  [obstacles, collectibles, exits, enemies, players]
t_map	*check_map_errors(char *path)
{
	int			fd;
	char		*line;
	t_map		*map;
	static int	data[5];

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	map = malloc(sizeof(t_map));
	if (line == NULL)
		clean_exit("Error\n-> Map is empty or cannot be opened.", map);
	map->width = ft_line_len(line);
	map->heigth = 0;
	while (line != NULL)
	{
		map->heigth++;
		check_errors_map_line(line, data, map);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (data[1] == 0 || data[2] == 0 || data[4] == 0)
		clean_exit("Error\n-> Not enough elements to play this map.", map);
	if (data[4] != 1)
		clean_exit("Error\n-> Too many players!", map);
	return (map);
}

void	check_errors_map_line(char *line, int data[5], t_map *map)
{
	int	i;

	i = -1;
	is_valid_map_line(line, ft_line_len(line), map);
	while (*(line + (++i)) != '\0')
	{
		if (*(line + i) == '1')
			data[0]++;
		if (*(line + i) == 'C')
			data[1]++;
		if (*(line + i) == 'E')
			data[2]++;
		if (*(line + i) == 'M')
			data[3]++;
		if (*(line + i) == 'P')
			data[4]++;
	}
}

void	is_valid_map_line(char *line, int l_len, t_map *map)
{
	int		i;
	char	c;

	if ((*line != '1') || *(line + l_len - 1) != '1')
		clean_exit("Error\n-> Map must be entirely surrounded by walls.", map);
	if (l_len != map->width)
	{
		free(line);
		clean_exit("Error\n-> Map must be rectangular.", map);
	}
	i = 0;
	while (i < l_len)
	{
		c = line[i];
		if (c != '0' && c != '1' && c != 'P'
			&& c != 'E' && c != 'C' && c != 'M' && c != '\n')
		{
			free(line);
			clean_exit("Error\n-> Found invalid character on map file.", map);
		}
		i++;
	}
}
