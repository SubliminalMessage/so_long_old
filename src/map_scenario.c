#include <so_long.h>

void    print_background(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (i < map->width)
    {
        j = 0;
        while (j < map->heigth + 1)
        {
            print_img(map, 0, i * 42, j * 42);
            j++;
        }
        i++;
    }

    print_borders(map);
    print_scenario(map, 0);
}

void    print_borders(t_map *map)
{
    int i;

    i = 0;
    while (++i < map->width - 1)
    {
        print_img(map, 2, i * 42, 0);
        print_img(map, 8, i * 42, (map->heigth - 1) * 42);
    }
    i = 0;
    while (++i < map->heigth - 1)
    {
        print_img(map, 4, 0, i * 42);
        print_img(map, 6, (map->width - 1) * 42, i * 42);
    }
    print_img(map, 1, 0, 0);
    print_img(map, 3, (map->width - 1) * 42, 0);
    print_img(map, 7, 0,  (map->heigth - 1) * 42);
    print_img(map, 9, (map->width - 1) * 42, (map->heigth - 1) * 42);
}

void    print_scenario(t_map *map, int e_idx)
{
    int i;
    int j;

    i = 0;
    while (++i < (map->width - 1))
    {
        j = 0;
        while (++j < (map->heigth - 1))
        {
            print_img(map, 5, i * 42, j * 42);
            if (map->at[j][i] == '1')
                print_img(map, 10, i * 42, j * 42);
            if (map->at[j][i] == 'E')
                print_img(map, 13, i * 42, j * 42);
            if (map->at[j][i] == 'C')
                print_img(map, 11, i * 42, j * 42);
            if (map->at[j][i] == 'P')
                print_img(map, 15, i * 42, j * 42);
            if (map->at[j][i] == 'M')
                print_img(map, 17, i * 42, j * 42);
            if (map->at[j][i] == 'M')
                map->p_enemy[e_idx++] = i * map->width + j;
        }
    }

    i = -1;
    while (++i < map->c_enemies)
        printf("ENEMY POS %d =>[%d][%d]\n", map->p_enemy[i], map->p_enemy[i] / map->width, map->p_enemy[i] % map->width);
}