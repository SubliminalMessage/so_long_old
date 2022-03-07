/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:59:24 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/07 14:32:24 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

// Reads the map file, parses it and stores it into a map struct
void	parse_map(t_map *map, char *path)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		clean_exit("Error\n-> Map is empty or cannot be opened.", map);
	map->at = malloc(sizeof(char *) * (map->heigth));
	i = -1;
	while (++i < map->heigth)
	{
		map->at[i] = malloc(sizeof(char) * (map->width));
		j = -1;
		while (++j < map->width)
			map->at[i][j] = *(line + j);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	check_parsed_map_errors(map);
}

void	check_parsed_map_errors(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = map->heigth - 1;
	while (++i < map->width - 1)
	{
		if (map->at[0][i] != '1' || map->at[j][i] != '1')
			clean_exit("Error\n-> Map must be surrounded by walls.", map);
	}
}
