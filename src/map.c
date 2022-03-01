/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:23:27 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/01 17:23:38 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <so_long.h>

void	*get_image(char *str, int *size, void *mlx)
{
	return (mlx_xpm_file_to_image(mlx, str, size, size));
}

void	map_setup_images(t_map *map, void *mlx)
{
	int size;

	size = 42;
	map->img_scen[0] = get_image("./assets/corner_tleft.xpm", &size, mlx);
	map->img_scen[1] = get_image("./assets/side_top.xpm", &size, mlx);
	map->img_scen[2] = get_image("./assets/corner_tright.xpm", &size, mlx);
	map->img_scen[3] = get_image("./assets/side_left.xpm", &size, mlx);
	map->img_scen[4] = get_image("./assets/tile.xpm", &size, mlx);
	map->img_scen[5] = get_image("./assets/side_right.xpm", &size, mlx);
	map->img_scen[6] = get_image("./assets/corner_dleft.xpm", &size, mlx);
	map->img_scen[7] = get_image("./assets/side_down.xpm", &size, mlx);
	map->img_scen[8] = get_image("./assets/corner_dright.xpm", &size, mlx);

	int i = 0;
	printf("[%2d] %p\n", i++, map->img_scen[0]);
	printf("[%2d] %p\n", i++, map->img_scen[1]);
	printf("[%2d] %p\n", i++, map->img_scen[2]);
	printf("[%2d] %p\n", i++, map->img_scen[3]);
	printf("[%2d] %p\n", i++, map->img_scen[4]);
	printf("[%2d] %p\n", i++, map->img_scen[5]);
	printf("[%2d] %p\n", i++, map->img_scen[6]);
	printf("[%2d] %p\n", i++, map->img_scen[7]);
	printf("[%2d] %p\n", i++, map->img_scen[8]);
}

t_map	*init_map(void *mlx)
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
	map_setup_images(map, mlx);
	return (map);
}

t_map	*parse_map(char *file_path, void *mlx)
{
	int		fd;
	char	*line;
	t_map	*map;

	fd = open(file_path, O_RDONLY);
	line = get_next_line(fd);
	map = init_map(mlx);
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