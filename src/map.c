/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:44:57 by dutch             #+#    #+#             */
/*   Updated: 2022/02/28 15:19:54 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->m_width = 0;
	map->m_heigth = 0;
	map->n_players = 0;
	map->n_enemies = 0;
	map->n_collectibles = 0;
	map->n_collects_picked = 0;
	map->n_obstacles = 0;
	map->n_exits = 0;
	map->player_pos = 0;
	map->enemies = NULL;
	map->obstacles = NULL;
	map->collectibles = NULL;
	map->colls_picked = NULL;
	map->exits = NULL;
	return (map);
}

t_map	*parse_map(char *file_path)
{
	int		fd;
	char	*line;
	t_map	*map;

	fd = open(file_path, O_RDONLY);
	line = get_next_line(fd);
	map = init_map();
	if (line == NULL)
		clean_exit("Error\n-> Map is empty or cannot be opened.", map);
	map->m_width = ft_strlen(line);
	while (line != NULL)
	{
		map->m_heigth++;
		map_info_from_line(line, map);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (map->n_collectibles == 0 || map->n_exits == 0 || map->n_players == 0)
		clean_exit("Error\n-> Not enough elements to play this map.", map);
	if (map->n_players != 1)
		clean_exit("Error\n-> Too many players!", map);
	get_map_positions(file_path, map);
	return (map);
}

void	map_info_from_line(char *line, t_map *map)
{
	int	i;

	i = -1;
	is_valid_map_line(line, ft_strlen(line), map);
	while (*(line + (++i)) != '\0')
	{
		if (*(line + i) == '1')
			map->n_obstacles++;
		if (*(line + i) == 'C')
			map->n_collectibles++;
		if (*(line + i) == 'E')
			map->n_exits++;
		if (*(line + i) == 'P')
			map->n_players++;
		if (*(line + i) == 'M')
			map->n_enemies++;
	}
}

void	is_valid_map_line(char *line, int l_len, t_map *map)
{
	int		i;
	char	c;

	if ((*line != '1')
		|| (*(line + l_len - 1) == '\n' && *(line + l_len - 2) != '1') 
		|| (*(line + l_len - 1) != '\n' && *(line + l_len - 1) != '1'))
		clean_exit("Error\n-> Map must be entirely surrounded by walls.", map);
	if (l_len != map->m_width)
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

void	get_map_positions(char *file_path, t_map *map)
{
	int		fd;
	char	*line;
	int		line_number;

	fd = open(file_path, O_RDONLY);
	map->n_obstacles -= (((map->m_width - 1) * 2) + ((map->m_heigth - 2) * 2));
	map->enemies = ft_calloc(map->n_enemies, sizeof(int));
	map->obstacles = ft_calloc(map->n_obstacles, sizeof(int));
	map->collectibles = ft_calloc(map->n_collectibles, sizeof(int));
	map->colls_picked = ft_calloc(map->n_collectibles, sizeof(int));
	map->exits = ft_calloc(map->n_exits, sizeof(int));
	line = get_next_line(fd);
	line_number = 0;
	while (line != NULL)
	{
		get_positions_from_line(line, map, line_number);
		free(line);
		line = get_next_line(fd);
		line_number++;
	}
	close(fd);
}

void	get_positions_from_line(char *line, t_map *map, int l_num)
{
	static int	idx_enemies;
	static int	idx_obstacles;
	static int	idx_collectibles;
	static int	idx_exits;
	int			i;

	if (l_num == 0 || l_num == (map->m_heigth - 1))
		return ;
	i = 1;
	while (line[i] != '\0')
	{
		if (line[i] == 'P')
			map->player_pos = (map->m_width * l_num) + i;
		if (line[i] == '1' && (line[i + 1] != '\n' && line[i + 1] != '\0'))
			map->obstacles[idx_obstacles++] = (map->m_width * l_num) + i;
		if (line[i] == 'C')
			map->collectibles[idx_collectibles++] = (map->m_width * l_num) + i;
		if (line[i] == 'E')
			map->exits[idx_exits++] = (map->m_width * l_num) + i;
		if (line[i] == 'M')
			map->enemies[idx_enemies++] = (map->m_width * l_num) + i;
		i++;
	}
}