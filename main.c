/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:50:31 by miduarte          #+#    #+#             */
/*   Updated: 2025/08/12 10:42:21 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	setup_hooks_and_loop(t_vars *vars)
{
	mlx_loop_hook(vars->mlx, ft_render, vars);
	mlx_hook(vars->win, KeyPress, KeyPressMask, handle_keypress, vars);
	mlx_hook(vars->win, KeyRelease, KeyReleaseMask, handle_keyrelease, vars);
	mlx_hook(vars->win, 17, 0, xclose, vars);
	mlx_loop(vars->mlx);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (check_args_and_load_map(argc, argv, &vars))
		return (1);
	set_player_start(&vars);
	setup_vars(&vars);
	print_boot_message();
	if (setup_window_and_textures(&vars))
		return (1);
	load_idle_sprites(&vars);
	setup_hooks_and_loop(&vars);
	xclose(&vars);
	return (0);
}
