/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:23:18 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/01 18:10:28 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void print_map_borders(t_map *map,  void *mlx, void *mlx_win)
{
    int w;
    int h;
    int sz;

    w = map->m_width;
    h = map->m_heigth;
    sz = 42;
    mlx_put_image_to_window(mlx, mlx_win, map->img_scen[0], 0, 0);
    mlx_put_image_to_window(mlx, mlx_win, map->img_scen[2], 0, 0);
    mlx_put_image_to_window(mlx, mlx_win, map->img_scen[6], 0, 0);
    mlx_put_image_to_window(mlx, mlx_win, map->img_scen[8], 0, 0);
}