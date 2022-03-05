#include <so_long.h>

// id == 0 => Auto
// id == 1 => Player
// id == 2 => Enemy
void print_at(int position, t_map *map, int id)
{
    int i;
    int j;

    i = position / map->width; // Y
    j = position % map->width; // X
    if (id == 1)
        print_img(map, 15 + map->next_frame % 2, j * 42, i * 42);
    if (id == 2)
        print_img(map, 17 + map->next_frame % 4, j * 42, i * 42);
    if (id == 0)
    {
        print_img(map, 5, j * 42, i * 42);
        if (map->at[i][j] == 'C')
            print_img(map, 11, j * 42, i * 42);
        if (map->at[i][j] == 'c')
            print_img(map, 12, j * 42, i * 42);
        if (map->at[i][j] == 'E')
            print_img(map, 13, j * 42, i * 42);
        if (map->at[i][j] == 'e')
            print_img(map, 14, j * 42, i * 42);
    }
}

// w => Up
// d => Right
// s => Down
// a => Left
void    player_move(char dir, t_map *map)
{
    int new_pos;
    int i;
    int j;

    new_pos = map->p_pos;
    if (dir == 'w')
        new_pos -= map->width;
    if (dir == 'd')
        new_pos += 1;
    if (dir == 's')
        new_pos += map->width;
    if (dir == 'a')
        new_pos -= 1;

    i = new_pos / map->width; // Y
    j = new_pos % map->width; // X

   // printf("Trying to move to [%d][%d] ('%c')\n", i, j, map->at[i][j]);
    if (map->at[i][j] == '1')
        return ;
    check_event_triggers(new_pos, map);
    print_at(map->p_pos, map, 0);
    print_at(new_pos, map, 1);
    print_current_moves(map);
    map->p_pos = new_pos;
}

void    check_event_triggers(int pos, t_map *map)
{
    int i;
    int j;
    int k;

    i = pos / map->width; // Y
    j = pos % map->width; // X
    if (map->at[i][j] == 'e')
        clean_exit("Congrats! You've won!\n", map);
    k = -1;
    while (++k < map->c_enemies)
    {
        if (map->p_enemy[k] == pos)
            clean_exit("Oops.. You lost\n", map);
    }
    if (map->at[i][j] == 'C')
    {
        map->at[i][j] = 'c';
        map->c_buttons--;
        if (map->c_buttons <= 0)
            open_all_doors(map);
    }
}

void    open_all_doors(t_map *map)
{
    int i;
    int j;

    i = -1;
    while (++i < map->heigth)
    {
        j = -1;
        while (++j < map->width)
        {
            //printf("Check! %d, %d\n", i, j);
            if (map->at[i][j] == 'E')
            {
                map->at[i][j] = 'e';
                print_at(i * map->width + j, map, 0);
            }
        }
    }
}

void    print_current_moves(t_map *map)
{
    static int moves = -1;
    char *text;
    char *itoa;
    int i;

    moves++;
    itoa = ft_itoa(moves);
    text = ft_strjoin("Movements: ", itoa);
    i = -1;
    while (++i < map->width)
        print_img(map, 0, i * 42, map->heigth * 42);
    i = 0xFFFFFFFF;
    mlx_string_put(map->mlx, map->win, 21, map->heigth * 42 + 21, i, text);
    free(itoa);
    free(text);
    (void) map;
}