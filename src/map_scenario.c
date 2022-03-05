#include <so_long.h>

void    print_background(t_map *m)
{
    int i;
    int j;

    i = 0;
    while (i < m->width)
    {
        j = 0;
        while (j < m->heigth + 1)
        {
            print_img(m, 0, i * 42, j * 42);
            j++;
        }
        i++;
    }
    print_borders(m);
    print_scenario(m, 0);
    m->at[m->p_pos/ m->width][m->p_pos % m->width] = '0';
    i = -1;
    while (++i < m->c_enemies)
    {
        printf("Enemy at %d\n", m->p_enemy[i]);
        m->at[m->p_enemy[i] / m->width][m->p_enemy[i] % m->width] = '0';
    }
    print_entities(m);
}

void    print_entities(t_map *map)
{
    int i;
    int j;
    int k;

    i = map->p_pos / map->width;
    j = map->p_pos % map->width;
    print_img(map, 15, j * 42, i * 42);
    k = -1;
    while (++k < map->c_enemies)
    {
        i = map->p_enemy[k] / map->width;
        j = map->p_enemy[k] % map->width;
        print_img(map, 17, j * 42, i * 42);
    }
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
    //print_current_moves(map);
}

void    print_scenario(t_map *map, int e_idx)
{
    int i;
    int j;

    i = 0;
    while (++i < (map->heigth - 1))
    {
        j = 0;
        while (++j < (map->width - 1))
        {
            print_img(map, 5, j * 42, i * 42);
            if (map->at[i][j] == '1')
                print_img(map, 10, j * 42, i * 42);
            if (map->at[i][j] == 'E')
                print_img(map, 13, j * 42, i * 42);
            if (map->at[i][j] == 'C')
                print_img(map, 11, j * 42, i * 42);
            if (map->at[i][j] == 'M')
                map->p_enemy[e_idx++] = i * map->width + j;
        }
    }

}