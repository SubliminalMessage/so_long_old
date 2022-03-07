/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:17:48 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/07 14:27:04 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	main(int argc, char **argv)
{
	t_map	*map;

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
	mlx_loop_hook(map->mlx, animation_frames, map);
	mlx_loop(map->mlx);
	return (0);
}

// Handles the animations
// 1 Animation frame per 1000 loop cycles
int	animation_frames(t_map *map)
{
	static int	frame_count = 0;

	frame_count++;
	if (frame_count >= 1000)
	{
		map->next_frame = (map->next_frame + 1) % 4;
		print_entities(map);
		frame_count = 0;
	}
	return (0);
}

// same as ft_strlen, but used for map lines
int	ft_line_len(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (*(line + len - 1) == '\n')
		len--;
	return (len);
}
