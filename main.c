/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:15 by miduarte          #+#    #+#             */
/*   Updated: 2025/06/24 16:38:58 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	xclose(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	write(1,"So Skong!\n", 9);
	exit(0);
}

int handleKeypress(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		xclose(vars);
	else if (keycode == XK_Up)
		vars->pos_y -= 10;
	else if (keycode == XK_Down)
		vars->pos_y += 10;
	else if (keycode == XK_Left)
		vars->pos_x -= 10;
	else if (keycode == XK_Right)
		vars->pos_x += 10;
	write(1,"Key Pressed: Idk\n", 17);
	return (0);
}
int	ft_render(t_vars *vars)
{
	static int	count = 0;
	if (++count >= 10000)
	{
		vars->frame = 1 - vars->frame; // Swap between 0 and 1
		count = 0;
	}
	vars->img.img = vars->sprites->idle[vars->frame];
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, vars->pos_x, vars->pos_y);
	return (0);
}

int	main(void)
{
	t_vars	vars;
	t_imgs	idleSprites;
	t_imgs	runSprites;
	int		img_width;
	int		img_height;
	vars.pos_x = 1920 / 2;
	vars.pos_y = 1080 / 2;

	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Silklong");
	idleSprites.idle[0] = mlx_xpm_file_to_image(vars.mlx, "./assets/hornetidle1.xpm", &img_width, &img_height);
	idleSprites.idle[1] = mlx_xpm_file_to_image(vars.mlx, "./assets/hornetidle2.xpm", &img_width, &img_height);
	runSprites.run[0] = mlx_xpm_file_to_image(vars.mlx, "./assets/AnyConv.com__hornetrun1.xpm", &img_width, &img_height);
	runSprites.run[1] = mlx_xpm_file_to_image(vars.mlx, "./assets/AnyConv.com__hornetrun2.xpm", &img_width, &img_height);
	runSprites.run[2] = mlx_xpm_file_to_image(vars.mlx, "./assets/AnyConv.com__hornetrun3.xpm", &img_width, &img_height);
	runSprites.run[3] = mlx_xpm_file_to_image(vars.mlx, "./assets/AnyConv.com__hornetrun4.xpm", &img_width, &img_height);
	runSprites.run[4] = mlx_xpm_file_to_image(vars.mlx, "./assets/AnyConv.com__hornetrun5.xpm", &img_width, &img_height);
	runSprites.run[5] = mlx_xpm_file_to_image(vars.mlx, "./assets/AnyConv.com__hornetrun6.xpm", &img_width, &img_height);
	runSprites.run[6] = mlx_xpm_file_to_image(vars.mlx, "./assets/AnyConv.com__hornetrun7.xpm", &img_width, &img_height);
	runSprites.run[7] = mlx_xpm_file_to_image(vars.mlx, "./assets/AnyConv.com__hornetrun8.xpm", &img_width, &img_height);
	

	vars.sprites = &idleSprites;
	vars.frame = 0;
	vars.img.img = idleSprites.idle[0];

	mlx_loop_hook(vars.mlx, ft_render, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, handleKeypress, &vars); 
	mlx_loop(vars.mlx);
	return (0);
}

/*
int	main(void)
{
	void	*mlx;
	void	*img;
	char	*relative_path = "./test.xpm";
	int		img_width;
	int		img_height;

	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
}*/