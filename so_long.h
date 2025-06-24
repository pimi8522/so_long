/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miduarte <miduarte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:28:59 by miduarte          #+#    #+#             */
/*   Updated: 2025/06/24 17:00:24 by miduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <stdlib.h>

#define RUN_FRAMES 8
#define IDLE_FRAMES 2

typedef struct s_imgs {
    void *idle[IDLE_FRAMES];
    void *run[RUN_FRAMES];
}   t_imgs;

typedef enum e_state {
    STATE_IDLE,
    STATE_RUN
}   t_state;

typedef struct s_data {
	void *img;
	char *adr;
	int bits_per_pixel;
	int line_length;
	int endian;
}	t_data;

typedef struct s_vars {
    void    *mlx;
    void    *win;
    t_imgs  sprites;
    int     pos_x;
    int     pos_y;
    t_state state;
    int     anim_frame; // frame for animation
}   t_vars;t_vars;

