/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:42 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 10:36:24 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_grid_x(int pos_x, int dx)
{
	int	gx;

	gx = pos_x + dx;
	gx = gx / TILE_SIZE;
	return (gx);
}

int	get_grid_y(int pos_y, int dy)
{
	int	gy;

	gy = pos_y + dy;
	gy = gy / TILE_SIZE;
	return (gy);
}

void	handle_collectible(t_vars *vars)
{
	vars->collected++;
	ft_printf("Collected Mask Shard!\n");
}

int	handle_exit(t_vars *vars)
{
	if (vars->collected == vars->total_collectibles)
	{
		ft_printf("Shaw long!\n");
		xclose(vars);
		return (1);
	}
	ft_printf("I mustn't release yet...\n");
	return (0);
}

void	move_player_to_new_pos(t_vars *vars, int dx, int dy)
{
	int	gx;
	int	gy;

	gx = get_grid_x(vars->pos_x, dx);
	gy = get_grid_y(vars->pos_y, dy);
	vars->pos_x += dx;
	vars->pos_y += dy;
	vars->map[gy][gx] = 'P';
	ft_printf("Moves: %d\n", vars->moves);
	vars->moves++;
}
