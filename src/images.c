/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dutch <dutch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:23:18 by dangonza          #+#    #+#             */
/*   Updated: 2022/03/02 00:05:06 by dutch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void print_map_borders(t_map *map,  void *m, void *v)
{
    int w;
    int h;
    int i;

    w = map->m_width - 1;
    h = map->m_heigth - 1;
    mlx_put_image_to_window(m, v, map->img_scen[0], 0, 0);
    mlx_put_image_to_window(m, v, map->img_scen[2], 42 * w, 0);
    mlx_put_image_to_window(m, v, map->img_scen[6], 0, 42 * h);
    mlx_put_image_to_window(m, v, map->img_scen[8], 42 * w, 42 * h);
    i = 0;
    while (++i < w)
    {
        mlx_put_image_to_window(m, v, map->img_scen[1], 42 * i, 0);
        mlx_put_image_to_window(m, v, map->img_scen[7], 42 * i, h * 42);
    }
    i = 0;
    while (++i < h)
    {
        mlx_put_image_to_window(m, v, map->img_scen[3], 0, 42 * i);
        mlx_put_image_to_window(m, v, map->img_scen[5], w * 42, 42 * i);
    }
}

void print_screen_background(t_map *map, void *mlx, void *win)
{
    void *bkgr;
    int size;
    int i;
    int j;

    size = 42;
    bkgr = get_image("./assets/xpm/background.xpm", &size, mlx);
    i = 0;
    j = 0;
    while (i < (map->m_width - 1))
    {
        j = 0;
        while (j < (map->m_heigth - 1))
        {
            if (i + j == 0)
        }
    }
}