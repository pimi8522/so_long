/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gauntlet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:55:11 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/11 16:19:20 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int count_item(char **map, char item)
{
    int y;
    int cnt;
    
    y = 0;
    cnt = 0;
    while (map[y])
    {
        cnt += count_item_row(map[y], item);
        y++;
    }
    return (cnt);
}

static int map_basic_checks(char **map)
{
    if (!map)
        return (0);
    if (!map[0])
        return (0);
    if (!valid_rectangle(map))
        return (0);
    if (!valid_chars(map))
        return (0);
    return (1);
}

static int map_wall_and_item_checks(char **map)
{
    if (!walls_closed(map))
        return (0);
    if (count_item(map, 'P') != 1)
        return (0);
    if (count_item(map, 'E') != 1)
        return (0);
    if (count_item(map, 'C') <= 0)
        return (0);
    return (1);
}

static int map_flood_check(char **map)
{
    char **tmp;
    int py;
    int px;
    int result;
    
    tmp = dup_map(map);
    if (!tmp)
        return (0);
    result = 1;
    if (!find_start(tmp, &py, &px))
        result = 0;
    if (result)
        flood_fill(tmp, py, px);
    if (result && (count_item(tmp, 'C') > 0 || count_item(tmp, 'E') == 1))
        result = 0;
    free_dup(tmp);
    return (result);
}

int map_gauntlet(char **map)
{
    if (!map_basic_checks(map))
        return (0);
    if (!map_wall_and_item_checks(map))
        return (0);
    if (!map_flood_check(map))
        return (0);
    return (1);
}

