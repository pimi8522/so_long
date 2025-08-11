/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:51:59 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/11 16:19:57 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int walls_closed(char **map)
{
    int rows;
    int y;
    
    rows = map_row_count(map);
    if (!wall_row_closed(map[0]))
        return (0);
    if (!wall_row_closed(map[rows - 1]))
        return (0);
    y = 0;
    while (y < rows)
    {
        if (!wall_sides_closed(map[y]))
            return (0);
        y++;
    }
    return (1);
}

int valid_rectangle_row(char **map, int len)
{
    int y;
    
    y = 1;
    while (map[y])
    {
        if ((int)ft_strlen(map[y]) != len)
            return (0);
        y++;
    }
    return (1);
}

int valid_rectangle(char **map)
{
    int len;
    
    len = ft_strlen(map[0]);
    return valid_rectangle_row(map, len);
}

int valid_char_row(char *row)
{
    int x;
    char c;
    
    x = 0;
    while ((c = row[x]))
    {
        if (c != '1' && c != '0' && c != 'C'
         && c != 'E' && c != 'P')
            return (0);
        x++;
    }
    return (1);
}

int valid_chars(char **map)
{
    int y;
    
    y = 0;
    while (map[y])
    {
        if (!valid_char_row(map[y]))
            return (0);
        y++;
    }
    return (1);
}