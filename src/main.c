/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dutch <dutch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 22:09:09 by dutch             #+#    #+#             */
/*   Updated: 2022/02/27 12:14:27 by dutch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	leaks()
{
	system("leaks so_long");
}

void	clean_exit(char *error, t_map *map)
{
	printf("%s\n", error);
	if (map != NULL)
	{
		if (map->enemies != NULL)
			free(map->enemies);
		if (map->obstacles != NULL)
			free(map->obstacles);
		if (map->collectibles != NULL)
			free(map->collectibles);
		if (map->exits != NULL)
			free(map->exits);
		free(map);
	}
	exit(0);
}

int main(int argc, char **argv)
{
	//void	*mlx;
	//void	*mlx_win;
	t_map	*map;

	atexit(leaks);
	if (argc < 2)
		clean_exit("Error\n-> A map file is needed.", NULL);
	if (ft_strncmp((ft_strrchr(argv[1], '\0')) - 4, ".ber", 4) != 0)
		clean_exit("Error\n-> Map must a '.ber' extension file.", NULL);
	map = parse_map(argv[1]);
	printf("Everything OK\n");

/*
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
*/

}
