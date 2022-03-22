/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:16:21 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/22 17:40:49 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long_bonus.h>

// Given a map struct, initializes pointers & images
void	set_map_config(t_map *map)
{
	set_pointers(map);
	set_images(map);
	map->p_enemy = malloc(sizeof(int) * (map->c_enemies));
}

// Given a map struct, initializes MLX pointers
void	set_pointers(t_map *map)
{
	int		w;
	int		h;
	char	*title;

	w = map->width * 42;
	h = (map->heigth + 1) * 42;
	title = "So long no see";
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, w, h, title);
}

// Given a map struct, initalizes MLX images' pointers
void	set_images(t_map *map)
{
	map->imgs[0] = get_img("./assets/xpm/background.xpm", map);
	map->imgs[1] = get_img("./assets/xpm/corner_tleft.xpm", map);
	map->imgs[2] = get_img("./assets/xpm/side_top.xpm", map);
	map->imgs[3] = get_img("./assets/xpm/corner_tright.xpm", map);
	map->imgs[4] = get_img("./assets/xpm/side_left.xpm", map);
	map->imgs[5] = get_img("./assets/xpm/tile.xpm", map);
	map->imgs[6] = get_img("./assets/xpm/side_right.xpm", map);
	map->imgs[7] = get_img("./assets/xpm/corner_dleft.xpm", map);
	map->imgs[8] = get_img("./assets/xpm/side_down.xpm", map);
	map->imgs[9] = get_img("./assets/xpm/corner_dright.xpm", map);
	map->imgs[10] = get_img("./assets/xpm/rock.xpm", map);
	map->imgs[11] = get_img("./assets/xpm/button_normal.xpm", map);
	map->imgs[12] = get_img("./assets/xpm/button_pressed.xpm", map);
	map->imgs[13] = get_img("./assets/xpm/exit_closed.xpm", map);
	map->imgs[14] = get_img("./assets/xpm/exit_open.xpm", map);
	map->imgs[15] = get_img("./assets/xpm/player_01.xpm", map);
	map->imgs[16] = get_img("./assets/xpm/player_02.xpm", map);
	map->imgs[17] = get_img("./assets/xpm/enemy_01.xpm", map);
	map->imgs[18] = get_img("./assets/xpm/enemy_02.xpm", map);
	map->imgs[19] = get_img("./assets/xpm/enemy_03.xpm", map);
	map->imgs[20] = get_img("./assets/xpm/enemy_04.xpm", map);
}

// Given a file path, return (void *) pointing to that image
void	*get_img(char *path, t_map *map)
{
	int		size;
	void	*img;

	size = 42;
	img = mlx_xpm_file_to_image(map->mlx, path, &size, &size);
	if (img == NULL)
		clean_exit("Error\n-> Error encountered reading image file", map);
	return (img);
}

// Given an image index and its position, prints the image into the window.
void	print_img(t_map *map, int index, int x, int y)
{
	mlx_put_image_to_window(map->mlx, map->win, map->imgs[index], x, y);
}
