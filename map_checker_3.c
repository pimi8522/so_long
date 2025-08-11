/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:52:48 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/11 16:19:42 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int find_start_row(char *row, int *out_x)
{
    int x;
    
    x = 0;
    while (row[x])
    {
        if (row[x] == 'P')
        {
            *out_x = x;
            return (1);
        }
        x++;
    }
    return (0);
}

int find_start(char **m, int *out_y, int *out_x)
{
    int y;
    
    y = 0;
    while (m[y])
    {
        if (find_start_row(m[y], out_x))
        {
            *out_y = y;
            return (1);
        }
        y++;
    }
    return (0);
}

void flood_fill(char **m, int y, int x)
{
    if (y < 0 || x < 0)
        return;
    if (!m[y] || !m[y][x])
        return;
    if (m[y][x] == '1' || m[y][x] == 'F')
        return;
    m[y][x] = 'F';
    flood_fill(m, y + 1, x);
    flood_fill(m, y - 1, x);
    flood_fill(m, y, x + 1);
    flood_fill(m, y, x - 1);
}

int wall_row_closed(char *row)
{
    int x;
    
    x = 0;
    while (row[x])
    {
        if (row[x] != '1')
            return (0);
        x++;
    }
    return (1);
}

int wall_sides_closed(char *row)
{
    int len;
    
    len = ft_strlen(row);
    if (row[0] != '1' || row[len - 1] != '1')
        return (0);
    return (1);
}
