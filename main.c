#include "so_long.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include "./minilibx-linux/mlx.h"
#include "./minilibx-linux/mlx_int.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "get_next_line.h"

#define RUN_FRAMES   3
#define IDLE_FRAMES  5
#define TILE_SIZE    100  // pixels per map cell

typedef enum e_state
{
    STATE_IDLE,
    STATE_RUN
}           t_state;

typedef struct s_imgs
{
    void    *idle[IDLE_FRAMES];
    void    *run[RUN_FRAMES];
}           t_imgs;

typedef struct s_map_textures
{
    void    *wall;
    void    *floor;
    void    *collectible;
    void    *exit;
    void    *player;
}           t_map_textures;

typedef struct s_vars
{
    void            *mlx;
    void            *win;
    t_imgs          sprites;
    int             pos_x;
    int             pos_y;
    t_state         state;
    int             anim_frame;
    char            **map;
    t_map_textures  map_textures;
}               t_vars;

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
 * Load the .ber file into a NULL-terminated array of strings.
 */
char **load_map(const char *filename)
{
    int     fd;
    char    *line;
    char    **map;
    int     rows;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (NULL);
    }
    map = NULL;
    rows = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        map = realloc(map, sizeof(char *) * (rows + 1));
        if (!map)
        {
            perror("Error allocating memory");
            close(fd);
            return (NULL);
        }
        map[rows++] = line;
    }
    map = realloc(map, sizeof(char *) * (rows + 1));
    if (!map)
    {
        perror("Error reallocating memory");
        close(fd);
        return (NULL);
    }
    map[rows] = NULL;
    close(fd);
    return (map);
}

/*
 * Free the map array.
 */
void free_map(char **map)
{
    int i;

    i = 0;
    while (map && map[i])
        free(map[i++]);
    free(map);
}

/*
 * Find the player 'P' in map, set pos_x/pos_y (in pixels), replace with '0'.
 */
static void set_player_start(t_vars *vars)
{
    int y;
    int x;

    y = 0;
    while (vars->map[y])
    {
        x = 0;
        while (vars->map[y][x])
        {
            if (vars->map[y][x] == 'P')
            {
                vars->pos_x = x * TILE_SIZE;
                vars->pos_y = y * TILE_SIZE;
                vars->map[y][x] = '0';
                return;
            }
            x++;
        }
        y++;
    }
}

/*
 * Load all map tile textures.
 */
int load_map_textures(t_vars *vars)
{
    int w, h;

    vars->map_textures.wall = mlx_xpm_file_to_image(vars->mlx,
            "./assets/wall.xpm", &w, &h);
    vars->map_textures.floor = mlx_xpm_file_to_image(vars->mlx,
            "./assets/floor.xpm", &w, &h);
    vars->map_textures.collectible = mlx_xpm_file_to_image(vars->mlx,
            "./assets/collectible.xpm", &w, &h);
    vars->map_textures.exit = mlx_xpm_file_to_image(vars->mlx,
            "./assets/floor.xpm", &w, &h);
    vars->map_textures.player = mlx_xpm_file_to_image(vars->mlx,
            "./assets/floor.xpm", &w, &h);
    if (!vars->map_textures.wall || !vars->map_textures.floor
     || !vars->map_textures.collectible || !vars->map_textures.exit
     || !vars->map_textures.player)
        return (0);
    return (1);
}

/*
 * Draw the map to the window.
 */
void render_map(t_vars *vars)
{
    int x, y;
    void *img;

    y = 0;
    while (vars->map[y])
    {
        x = 0;
        while (vars->map[y][x])
        {
            img = NULL;
            if (vars->map[y][x] == '1')
                img = vars->map_textures.wall;
            else if (vars->map[y][x] == '0')
                img = vars->map_textures.floor;
            else if (vars->map[y][x] == 'C')
                img = vars->map_textures.collectible;
            else if (vars->map[y][x] == 'E')
                img = vars->map_textures.exit;
            /* player tile handled separately */
            if (img)
                mlx_put_image_to_window(vars->mlx,
                    vars->win, img, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
}

/*
 * Close callback: free resources and exit.
 */
int xclose(t_vars *vars)
{
    free_map(vars->map);
    mlx_destroy_window(vars->mlx, vars->win);
    mlx_destroy_display(vars->mlx);
    exit(0);
}
int  get_map_height(char **map)
{
    int rows = 0;
    while (map && map[rows])
        rows++;
    return (rows);
}
/*
 * Handle key presses: move one tile and switch to RUN state.
 */
static bool  can_move(t_vars *vars, int dx, int dy)
{
    int new_px = vars->pos_x + dx;
    int new_py = vars->pos_y + dy;
    int gx = new_px / TILE_SIZE;
    int gy = new_py / TILE_SIZE;

    /* 1) bounds check */
    if (gy < 0 || gy >= get_map_height(vars->map))
        return (false);
    if (gx < 0 || gx >= ft_strlen(vars->map[0]))
        return (false);
    /* 2) wall check */
    if (vars->map[gy][gx] == '1')
        return (false);
    return (true);
}

int handleKeypress(int keycode, t_vars *vars)
{
    if (keycode == XK_Escape)
        xclose(vars);
    else if (keycode == XK_Left && can_move(vars, -TILE_SIZE, 0))
    {
        vars->pos_x -= TILE_SIZE;
        vars->state = STATE_RUN;
    }
    else if (keycode == XK_Right && can_move(vars,  TILE_SIZE, 0))
    {
        vars->pos_x += TILE_SIZE;
        vars->state = STATE_RUN;
    }
    else if (keycode == XK_Up && can_move(vars, 0, -TILE_SIZE))
    {
        vars->pos_y -= TILE_SIZE;
        vars->state = STATE_RUN;
    }
    else if (keycode == XK_Down && can_move(vars, 0,  TILE_SIZE))
    {
        vars->pos_y += TILE_SIZE;
        vars->state = STATE_RUN;
    }
    return (0);
}

/*
 * Handle key release: return to IDLE state.
 */
int handleKeyRelease(int keycode, t_vars *vars)
{
    if (keycode == XK_Left || keycode == XK_Right
     || keycode == XK_Up   || keycode == XK_Down)
        vars->state = STATE_IDLE;
    return (0);
}

/*
 * Main render loop: draw map + player sprite.
 */
int ft_render(t_vars *vars)
{
    void *img;
    static int count = 0;

    render_map(vars);
    if (vars->state == STATE_RUN)
    {
        img = vars->sprites.run[vars->anim_frame];
        vars->anim_frame = (vars->anim_frame + 1) % RUN_FRAMES;
        /* after one run frame, go back to idle */
        vars->state = STATE_IDLE;
    }
    else
    {
        img = vars->sprites.idle[vars->anim_frame];
        if (++count >= 1000)
        {
            vars->anim_frame = (vars->anim_frame + 1) % IDLE_FRAMES;
            count = 0;
        }
    }
    mlx_put_image_to_window(vars->mlx,
        vars->win, img, vars->pos_x, vars->pos_y);
    return (0);
}


int main(int argc, char **argv)
{
    t_vars vars;
    int    w, h;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file.ber>\n", argv[0]);
        return (1);
    }
    vars.map = load_map(argv[1]);
    if (!vars.map)
        return (1);
    set_player_start(&vars);

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx,
        TILE_SIZE * ft_strlen(vars.map[0]),
        TILE_SIZE * get_map_height(vars.map),
        "Silklong");

    if (!load_map_textures(&vars))
    {
        fprintf(stderr, "Error loading map textures\n");
        free_map(vars.map);
        return (1);
    }

    vars.state = STATE_IDLE;
    vars.anim_frame = 0;

    /* load idle/run sprites */
    vars.sprites.idle[0] = mlx_xpm_file_to_image(vars.mlx,
        "./assets/idle0.xpm", &w, &h);
    vars.sprites.idle[1] = mlx_xpm_file_to_image(vars.mlx,
        "./assets/idle1.xpm", &w, &h);
    vars.sprites.idle[2] = mlx_xpm_file_to_image(vars.mlx,
        "./assets/idle2.xpm", &w, &h);
    vars.sprites.idle[3] = mlx_xpm_file_to_image(vars.mlx,
        "./assets/idle3.xpm", &w, &h);
    vars.sprites.idle[4] = mlx_xpm_file_to_image(vars.mlx,
        "./assets/idle4.xpm", &w, &h);

    vars.sprites.run[0] = mlx_xpm_file_to_image(vars.mlx,
        "./assets/run0.xpm", &w, &h);
    vars.sprites.run[1] = mlx_xpm_file_to_image(vars.mlx,
        "./assets/run1.xpm", &w, &h);
    vars.sprites.run[2] = mlx_xpm_file_to_image(vars.mlx,
        "./assets/run2.xpm", &w, &h);

    mlx_loop_hook(vars.mlx, ft_render, &vars);
    mlx_hook(vars.win, KeyPress,   KeyPressMask,   handleKeypress,    &vars);
    mlx_hook(vars.win, KeyRelease, KeyReleaseMask, handleKeyRelease, &vars);
    mlx_loop(vars.mlx);

    free_map(vars.map);
    return (0);
}