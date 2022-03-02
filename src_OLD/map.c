/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:23:27 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/02 13:13:44 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <so_long.h>

void	*get_image(char *str, int *size, void *mlx)
{
	return (mlx_xpm_file_to_image(mlx, str, size, size));
}

void	put_image(void *img, void *mlx, void *win, int x, int y)
{
	mlx_put_image_to_window(mlx, win, img, x, y);
}

void	map_setup_images(t_map *map, void *mlx)
{
	int size;

	size = 42;
	map->img_scen[0] = get_image("./assets/xpm/corner_tleft.xpm", &size, mlx);
	map->img_scen[1] = get_image("./assets/xpm/side_top.xpm", &size, mlx);
	map->img_scen[2] = get_image("./assets/xpm/corner_tright.xpm", &size, mlx);
	map->img_scen[3] = get_image("./assets/xpm/side_left.xpm", &size, mlx);
	map->img_scen[4] = get_image("./assets/xpm/tile.xpm", &size, mlx);
	map->img_scen[5] = get_image("./assets/xpm/side_right.xpm", &size, mlx);
	map->img_scen[6] = get_image("./assets/xpm/corner_dleft.xpm", &size, mlx);
	map->img_scen[7] = get_image("./assets/xpm/side_down.xpm", &size, mlx);
	map->img_scen[8] = get_image("./assets/xpm/corner_dright.xpm", &size, mlx);

	int i = 0;
	printf("---------------");
	printf("[%2d] %p\n", i++, map->img_scen[0]);
	printf("[%2d] %p\n", i++, map->img_scen[1]);
	printf("[%2d] %p\n", i++, map->img_scen[2]);
	printf("[%2d] %p\n", i++, map->img_scen[3]);
	printf("[%2d] %p\n", i++, map->img_scen[4]);
	printf("[%2d] %p\n", i++, map->img_scen[5]);
	printf("[%2d] %p\n", i++, map->img_scen[6]);
	printf("[%2d] %p\n", i++, map->img_scen[7]);
	printf("[%2d] %p\n", i++, map->img_scen[8]);
	printf("---------------");
}

t_map	*init_map(void *mlx)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->m_width = 0;
	map->m_heigth = 0;
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
	return (map);
}

//  [obstacles, collectibles, exits, enemies, players]
void	map_info_from_line(char *line, t_map *map)
{
	int	i;
	static int data[5];

	i = -1;
	is_valid_map_line(line, ft_strlen(line), map);
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
