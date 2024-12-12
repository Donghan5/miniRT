/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:51:26 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/10 12:59:21 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_ray get_ray(int x, int y, t_info *info)
{
    t_ray ray;
    t_camera camera = info->scene.camera;

    ray.origin = camera.coordinates;

    double fov = camera.c_view * M_PI / 180.0;
    double px = (2.0 * ((double)x / SCREEN_WIDTH) - 1.0) * tan(fov/2.0);
    double py = -(2.0 * ((double)y / SCREEN_HEIGHT) - 1.0) * tan(fov/2.0) * SCREEN_HEIGHT / SCREEN_WIDTH;
    t_vec3 dir = vec3_normalize(vec3(1.0, py, px));
    t_vec3 target = vec3_normalize(camera.orientation);
    if (target.x != 0 || target.y != 0 || target.z != 0) {
        t_vec3 world_up = {0, 1, 0};
        t_vec3 right = vec3_normalize(vec3_cross(target, world_up));
        t_vec3 up = vec3_normalize(vec3_cross(right, target));
        t_vec3 forward = target;
        ray.direction = vec3_normalize(vec3(
            dir.x * forward.x + dir.y * up.x + dir.z * right.x,
            dir.x * forward.y + dir.y * up.y + dir.z * right.y,
            dir.x * forward.z + dir.y * up.z + dir.z * right.z
        ));
    } else {
        ray.direction = dir;
    }
    return ray;
}

static void put_pixels_to_image(t_info *info, int y, int x, t_color pixel_color)
{
	unsigned int	color;
	int				i;
	int				j;
	int				scale;

	i = 0;
	scale = 1;
    if (info->toggle_mode != TOGGLE_FULL && info->render_type == LOW_RENDER)
        scale = 8;
	color = (pixel_color.r << 16) | (pixel_color.g << 8) | pixel_color.b;
	while (i < scale && (y + i) < SCREEN_HEIGHT) {
		j = 0;
		while (j < scale && (x + j) < SCREEN_WIDTH) {
			char *dst = info->img->addr + ((y + i) * info->img->line_length +
						(x + j) * (info->img->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

void render_scene(t_info *info)
{
    int		scale;
	t_color pixel_color;
	int		y;
	int		x;
	t_ray	ray;

    scale = 1;
    if (info->toggle_mode != TOGGLE_FULL && info->render_type == LOW_RENDER)
        scale = 8;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
            ray = get_ray(x + 0.5, y + 0.5, info);
            pixel_color = trace_ray(ray, info, 0);
            pixel_color.r = (int)fmin(255, fmax(0, pixel_color.r));
            pixel_color.g = (int)fmin(255, fmax(0, pixel_color.g));
            pixel_color.b = (int)fmin(255, fmax(0, pixel_color.b));

			put_pixels_to_image(info, y, x, pixel_color);
			x += scale;
		}
		y += scale;
	}
    if (info->render_type == LOW_RENDER && info->toggle_mode == TOGGLE_OFF)
        info->render_type = FULL_RENDER;
    else
        info->render_type = NO_RENDER;
}
