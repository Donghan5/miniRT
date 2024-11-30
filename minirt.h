/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:40:16 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/30 00:42:11 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "minilibx-linux/mlx.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <float.h>
# include <sys/time.h>
# define SCREEN_HEIGHT 1080
# define SCREEN_WIDTH 1920
# define MAX_REFLECTION_DEPTH 3
# define EPSILON 0.0001
# define SCROLL_DELAY 300

typedef struct s_vec3 {
    double	x;
    double	y;
    double	z;
}				t_vec3;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_ray {
    t_vec3	origin;
    t_vec3	direction;
}				t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_ambient
{
	double	a_ratio;
	t_color	color;
}				t_ambient;

typedef struct s_camera
{
	t_vec3	coordinates;
	t_vec3	orientation;
	int		c_view;
}				t_camera;

typedef struct s_light
{
	t_vec3	coordinates;
	t_color	color;
	double	l_brightness;
}				t_light;

typedef struct s_sphere
{
	t_vec3	coordinates;
	t_color	color;
	double	sp_diameter;
}				t_sphere;

typedef struct s_plane
{
	t_vec3	coordinates;
	t_vec3	normal_vector;
	t_color	color;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3	coordinates;
	t_vec3	axis_vector;
	t_color	color;
	double	cy_diameter;
	double	cy_height;
}				t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	**sphere;
	t_plane		**plane;
	t_cylinder	**cylinder;
	int			sphere_n;
	int			plane_n;
	int			cylinder_n;
}				t_scene;

enum e_render_type
{
	NO_RENDER,
	LOW_RENDER,
	FULL_RENDER
};

typedef struct s_info
{
	t_data	*img;
	t_scene	scene;
	void	*mlx;
	void	*win;
	int		moving_map;
	int		rotating_map;
	int		moving_text;
	int		moving_origin_x;
	int		moving_origin_y;
	int		text_x;
	int		text_y;
	int		is_input;
	int		latest_key;
	long	last_scroll_time;
	int		render_type;
}				t_info;

t_vec3 vec3(double x, double y, double z);

t_vec3 vec3_add(t_vec3 a, t_vec3 b);

t_vec3 vec3_sub(t_vec3 a, t_vec3 b);

t_vec3 vec3_mul(t_vec3 v, double t);

t_vec3 vec3_hadamard(t_vec3 a, t_vec3 b);

double vec3_dot(t_vec3 a, t_vec3 b);

t_vec3 vec3_normalize(t_vec3 v);

t_vec3 vec3_reflect(t_vec3 v, t_vec3 n);

t_vec3 vec3_cross(t_vec3 a, t_vec3 b);

long	get_current_time_ms(void);

double	ft_atod(const char *str);

int		isEqual(double a, double b);

int		mouse_clicks(int keycode, int x, int y, t_info *info);
int		mouse_off(int keycode, int x, int y, t_info *info);
int		mouse_moves(int x, int y, t_info *info);

int		key_pressed(int keycode, t_info *info);
int		key_off(int keycode, t_info *info);
void	parse_scene(char *path, t_scene *scene);
int		render_next_frame(t_info *info);
void	exit_error(t_scene scene, int free_index_limit, char *message);
void	ft_putstr_fd(char *s, int fd);

void	render_scene(t_info *info);
int		close_window(t_info *info);
int		render_next_frame(t_info *info);
void	free_scene(t_scene *scene);

#endif
