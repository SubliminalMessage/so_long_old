/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dutch <dutch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:17:33 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/04 23:55:08 by dutch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	leaks(void)
{
	system("leaks so_long");
}

int	main(int argc, char **argv)
{
	t_map	*map;

	atexit(leaks);
	if (argc < 2)
		clean_exit("Error\n-> A map file is needed.", NULL);
	if (ft_strncmp((ft_strrchr(argv[1], '\0')) - 4, ".ber", 4) != 0)
		clean_exit("Error\n-> Map must a '.ber' extension file.", NULL);
	map = check_map_errors(argv[1]);
	parse_map(map, argv[1]);
	set_map_config(map);

	print_background(map);
	print_current_moves(map);

	mlx_key_hook(map->win, handle_key, map);
	mlx_hook(map->win, 17, 1L < 17, window_close, map);
	mlx_loop(map->mlx);

	//clean_exit(NULL, map);
	return (0);
}

int	ft_line_len(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (*(line + len - 1) == '\n')
		len--;
	return (len);
}
