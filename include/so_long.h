/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:18:36 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/03 18:45:16 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>

typedef struct s_map {
	int		width;
	int		heigth;
	void	*mlx;
	void	*win;
	void	*imgs[21];
	int		buttons;
	char	**at;
}	t_map;

void	clean_exit(char *msg, t_map *map);
t_map	*check_map_errors(char *path);
void	is_valid_map_line(char *line, int l_len, t_map *map);
//void	map_info_from_line(char *line, t_map *map);
void	check_errors_map_line(char *line, int data[5], t_map *map);
int		ft_line_len(char *line);
void	parse_map(t_map *map, char *path);
#endif