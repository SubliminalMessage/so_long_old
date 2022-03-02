/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:18:36 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/02 14:57:19 by dangonza         ###   ########.fr       */
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
}	t_map;

void	clean_exit(char *msg, void *ptr_free);
t_map	*check_map_errors(char *path);
#endif