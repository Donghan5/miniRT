/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:48:45 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/25 21:13:14 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_info_block(t_info *info)
{
	char			*data;
	unsigned int	white;

	white = 0xFFFFFFFF;
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y, white, "miniRT. Controls:");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 15, white, "Esc/Q          Exit");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 30, white, "Mouse L        Camera rotation");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 45, white, "WASD           Movement");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 60, white, "info");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 75, white, "info2");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 95, white, "data");
	data = ft_itoa(info->scene.camera.coordinates.x);
	mlx_string_put(info->mlx, info->win, info->text_x + 90,
		info->text_y + 95, white, data);
	free (data);
}

int	is_render(t_info *info)
{
	if (info->moving_text ||  info->moving_map || info->is_input || 
        ((get_current_time_ms() - info->last_scroll_time) < SCROLL_DELAY))
	{
		info->render_type = LOW_RENDER;
		return (1);
	}
	if (info->render_type != NO_RENDER)
		return (1);
	return (0);
}

int	render_next_frame(t_info *info)
{
	if (!is_render(info))
		return (0);
	render_scene(info);
	mlx_do_sync(info->mlx);
	mlx_put_image_to_window(info->mlx, info->win, info->img->img, 0, 0);
	print_info_block(info);
	mlx_destroy_image(info->mlx, info->img->img);
	info->img->img = mlx_new_image(info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	info->img->addr = mlx_get_data_addr(info->img->img,
			&info->img->bits_per_pixel, &info->img->line_length,
			&info->img->endian);
	return (0);
}
