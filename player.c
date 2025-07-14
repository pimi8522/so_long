/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:42 by miduarte          #+#    #+#             */
/*   Updated: 2025/07/14 11:25:43 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_vars *vars, int dx, int dy)
{
	int		gx = (vars->pos_x + dx) / TILE_SIZE;
	int		gy = (vars->pos_y + dy) / TILE_SIZE;
	int		old_gx = vars->pos_x / TILE_SIZE;
	int		old_gy = vars->pos_y / TILE_SIZE;
	char	cell = vars->map[gy][gx];
	if (cell == '1')
		return ; // wall: no further action

	// Clear the player from the old position
	vars->map[old_gy][old_gx] = '0';

	if (cell == 'C')
	{
		vars->collected++;
		// -- COLLECT MESSAGE --
		ft_printf("Collected Mask Shard!\n");
	}

	if (cell == 'E')
	{
		if (vars->collected == vars->total_collectibles)
		{
			// -- SUCCESS EXIT MESSAGE --
			ft_printf("Shaw long!\n");
			xclose(vars);
		}
		else
		{
			// -- BLOCKED EXIT MESSAGE --
			ft_printf("I mustn't release yet...\n");
			// Restore player to old position
			vars->map[old_gy][old_gx] = 'P';
			return ;
		}
	}

	// Move player to the new position
	vars->pos_x += dx;
	vars->pos_y += dy;
	vars->map[gy][gx] = 'P';
		// -- MOVE MESSAGE --
	ft_printf("Moves: %d\n", vars->moves);
	vars->moves++;

}

