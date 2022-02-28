/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:09:09 by dutch             #+#    #+#             */
/*   Updated: 2022/02/28 17:26:00 by dangonza         ###   ########.fr       */
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
		if (map->enemies != NULL)
			free(map->enemies);
		if (map->obstacles != NULL)
			free(map->obstacles);
		if (map->collectibles != NULL)
			free(map->collectibles);
		if (map->colls_picked != NULL)
			free(map->colls_picked);
		if (map->exits != NULL)
			free(map->exits);
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
	map = parse_map(argv[1]);
	printf("Everything OK\n");
	/* PRINT MAP */
	/*printf("MAP: \n");
	printf("m_width => %d\n", map->m_width);
	printf("m_heigth => %d\n", map->m_heigth);
	printf("n_players => %d\n", map->n_players);
	printf("n_enemies => %d\n", map->n_enemies);
	printf("n_collectibles => %d\n", map->n_collectibles);
	printf("n_collects_picked => %d\n", map->n_collects_picked);
	printf("n_obstacles => %d\n", map->n_obstacles);
	printf("n_exits => %d\n", map->n_exits);
	printf("player_pos => %d\n", map->player_pos);*/
	/***************/

	mlx = mlx_init();
	//mlx_win = mlx_new_window(mlx, 42 * map->m_width, 42 * map->m_heigth, "Hello world!");
	mlx_win = mlx_new_window(mlx, 42 * 20, 42 * 20, "Hello world!");

	void	*img;
	char	*relative_path = "./assets/obstacles/scenario/tile.xmp";
	int		img_width = 42;
	int		img_height = 42;

	img = mlx_xpm_file_to_image(mlx, relative_path, &img_height, &img_width);
	if (img == NULL)
		printf("\nEs Null bro\n");
	printf("IMG: %p\n", img);
	printf("Height: %d\nWidth: %d\n", img_width, img_height);
	//mlx_put_image_to_window(mlx, mlx_win, img, 10, 10);
	//void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y


	mlx_loop(mlx);

	clean_exit(NULL, map);
}
