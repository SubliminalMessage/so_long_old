/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:23:44 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/02 13:16:09 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	leaks()
{
	system("leaks so_long");
}

void	clean_exit(char *error, t_map *map)
{
	if (error != NULL)
		printf("%s\n", error);
	if (map != NULL)
	{
		free(map);
	}
	exit(0);
}

int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_map	*map;

	atexit(leaks);
	if (argc < 2)
		clean_exit("Error\n-> A map file is needed.", NULL);
	if (ft_strncmp((ft_strrchr(argv[1], '\0')) - 4, ".ber", 4) != 0)
		clean_exit("Error\n-> Map must a '.ber' extension file.", NULL);

	mlx = mlx_init();
	map = parse_map(argv[1], mlx);
	printf("Everything OK\n");
 	printf("MAP: \n");
	printf("m_width => %d\n", map->m_width);
	printf("m_heigth => %d\n", map->m_heigth);
	printf("n_players => %d\n", map->n_players);
	printf("n_enemies => %d\n", map->n_enemies);
	printf("n_collectibles => %d\n", map->n_collectibles);
	printf("n_collects_picked => %d\n", map->n_collects_picked);
	printf("n_obstacles => %d\n", map->n_obstacles);
	printf("n_exits => %d\n", map->n_exits);
	printf("player_pos => %d\n", map->player_pos);
	
	//mlx_win = mlx_new_window(mlx, 42 * map->m_width, 42 * map->m_heigth, "Hello world!");
	mlx_win = mlx_new_window(mlx, 42 * map->m_width,
			42 * map->m_heigth, "So long no see...");

	int size = 42;
	void *background = mlx_xpm_file_to_image(mlx, "./assets/xpm/background.xpm", &size, &size);

	mlx_put_image_to_window(mlx, mlx_win, background, 0, 0);
	mlx_put_image_to_window(mlx, mlx_win, background, 0, 42);
	mlx_put_image_to_window(mlx, mlx_win, background, 0, 84);
	mlx_put_image_to_window(mlx, mlx_win, background, 42, 0);
	mlx_put_image_to_window(mlx, mlx_win, background, 42, 42);
	mlx_put_image_to_window(mlx, mlx_win, background, 42, 84);
	mlx_put_image_to_window(mlx, mlx_win, background, 84, 0);
	mlx_put_image_to_window(mlx, mlx_win, background, 84, 42);
	mlx_put_image_to_window(mlx, mlx_win, background, 84, 84);

	/*mlx_put_image_to_window(mlx, mlx_win, map->img_scen[0], 0, 0);
	mlx_put_image_to_window(mlx, mlx_win, map->img_scen[1], 42, 0);
	mlx_put_image_to_window(mlx, mlx_win, map->img_scen[2], 84, 0);

	mlx_put_image_to_window(mlx, mlx_win, map->img_scen[3], 0, 42);
	mlx_put_image_to_window(mlx, mlx_win, map->img_scen[4], 42, 42);
	mlx_put_image_to_window(mlx, mlx_win, map->img_scen[5], 84, 42);
	
	mlx_put_image_to_window(mlx, mlx_win, map->img_scen[6], 0, 84);
	mlx_put_image_to_window(mlx, mlx_win, map->img_scen[7], 42, 84);
	mlx_put_image_to_window(mlx, mlx_win, map->img_scen[8], 84, 84);*/

	print_map_borders(map, mlx, mlx_win);

	/*void	*img;
	char	*relative_path = "./assets/obstacles/scenario/tile.xmp";
	int		img_width = 42;
	int		img_height = 42;

	/img = mlx_xpm_file_to_image(mlx, relative_path, &img_height, &img_width);
	if (img == NULL)
		printf("\nEs Null bro\n");
	printf("IMG: %p\n", img);
	printf("Height: %d\nWidth: %d\n", img_width, img_height);
	//mlx_put_image_to_window(mlx, mlx_win, img, 10, 10);
	//void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y
*/

	mlx_loop(mlx);

	clean_exit(NULL, map);
}
