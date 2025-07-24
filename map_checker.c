/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:30:08 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/24 18:20:30 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>    // malloc, free

int	count_item(char **map, char item)
{
	int y, x, cnt;
	y = 0, x = 0, cnt = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == item)
				cnt++;
			x++;
		}
		y++;
	}
	return (cnt);
}

static char **dup_map(char **map)
{
    int rows = 0;
    while (map[rows]) rows++;

    char **copy = malloc((rows + 1) * sizeof(*copy));
    if (!copy)
        return NULL;

    for (int i = 0; i < rows; i++)
    {
        copy[i] = ft_strdup(map[i]);
        if (!copy[i])
        {
            // clean up everything we allocated so far
            while (i-- > 0)
                free(copy[i]);
            free(copy);
            return NULL;
        }
    }
    copy[rows] = NULL;
    return copy;
}

// free a duplicated map
static void free_dup(char **m)
{
    int i = 0;
    while (m[i])
        free(m[i++]);
    free(m);
}

// find the player start; returns 1 if found, 0 otherwise
static int find_start(char **m, int *out_y, int *out_x)
{
    int y = 0, x;
    while (m[y])
    {
        x = 0;
        while (m[y][x])
        {
            if (m[y][x] == 'P')
            {
                *out_y = y;
                *out_x = x;
                return (1);
            }
            x++;
        }
        y++;
    }
    return (0);
}

// recursive flood-fill, marking visited floors as 'F'
static void flood_fill(char **m, int y, int x)
{
    if (y < 0 || x < 0 || !m[y] || !m[y][x]) return;
    if (m[y][x] == '1' || m[y][x] == 'F')    return;
    m[y][x] = 'F';
    flood_fill(m, y + 1, x);
    flood_fill(m, y - 1, x);
    flood_fill(m, y, x + 1);
    flood_fill(m, y, x - 1);
}

static int walls_closed(char **map)
{
    int rows = 0;
    while (map[rows])
        rows++;

    // top row
    int x = 0;
    while (map[0][x])
    {
        if (map[0][x] != '1')
            return (0);
        x++;
    }

    // bottom row
    x = 0;
    while (map[rows - 1][x])
    {
        if (map[rows - 1][x] != '1')
            return (0);
        x++;
    }

    // left and right walls of each intermediate row
    int y = 0;
    while (y < rows)
    {
        int len = ft_strlen(map[y]);
        if (map[y][0] != '1' || map[y][len - 1] != '1')
            return (0);
        y++;
    }

    return (1);
}

// 1) ensure every row has same length
static int valid_rectangle(char **map)
{
    int y = 0;
    int len = ft_strlen(map[0]);

    while (map[++y])
    {
        if ((int)ft_strlen(map[y]) != len)
            return (0);
    }
    return (1);
}

// 2) ensure only valid characters appear
static int valid_chars(char **map)
{
    int y = 0, x;
    char c;

    while (map[y])
    {
        x = 0;
        while ((c = map[y][x]))
        {
            if (c != '1' && c != '0' && c != 'C'
             && c != 'E' && c != 'P')
                return (0);
            x++;
        }
        y++;
    }
    return (1);
}

int map_gauntlet(char **map)
{
    char **tmp;
    int   py, px;

    // 0) must be rectangle & only 1,0,C,E,P
    if (!map || !map[0]
     || !valid_rectangle(map)
     || !valid_chars(map))
        return (0);

    // 1) must be closed by walls  
    if (!walls_closed(map))
        return (0);

    // 2) basic item-count checks  
    if (count_item(map, 'P') != 1
     || count_item(map, 'E') != 1
     || count_item(map, 'C') <= 0)
        return (0);

    // 3) flood-fill setup  
    tmp = dup_map(map);
    if (!tmp)
        return (0);

    if (!find_start(tmp, &py, &px))
    {
        free_dup(tmp);
        return (0);
    }

    // 4) run flood-fill  
    flood_fill(tmp, py, px);

    // 5) ensure no unreachable 'C' or 'E'  
    if (count_item(tmp, 'C') > 0
     || count_item(tmp, 'E') == 1)
    {
        free_dup(tmp);
        return (0);
    }

    free_dup(tmp);
    return (1);
}