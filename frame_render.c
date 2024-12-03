/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:48:45 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/03 12:34:32 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_info_block(t_info *info)
{
	char			*data;
	unsigned int	low_color;
	unsigned int	full_color;
	unsigned int	gray;
	unsigned int	green;

	green = 0x32CD32;
	gray = 0xC0C0C0;
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y, gray, "miniRT. Controls:");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 15, gray, "Esc/Q          Exit");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 30, gray, "Mouse L        Camera and direction");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 45, gray, "Mouse R        Camera rotation");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 60, gray, "WASD           Movement");
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 75, gray, "Scroll         Up/Down");

	// mlx_string_put(info->mlx, info->win, info->text_x,
	// 	info->text_y + 75, white, "1              On/Off low resolution");

	low_color = gray;
	if (info->toggle_mode == TOGGLE_LOW)
		low_color = green;
	
	mlx_string_put(info->mlx, info->win, info->text_x,
	info->text_y + 90, gray, "1                        Low Resolution");
	mlx_string_put(info->mlx, info->win, info->text_x,
	info->text_y + 80, low_color, "                _____");
	mlx_string_put(info->mlx, info->win, info->text_x,
	info->text_y + 90, low_color, "               |");
	if (info->toggle_mode == TOGGLE_LOW)
		mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 90, gray, "                 ON");
	else
		mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 90, gray, "                 OFF");
	mlx_string_put(info->mlx, info->win, info->text_x,
	info->text_y + 90, low_color, "                     |");
	mlx_string_put(info->mlx, info->win, info->text_x,
	info->text_y + 90, low_color, "                _____");


	// mlx_string_put(info->mlx, info->win, info->text_x,
	// 	info->text_y + 90, white, "2              On/Off full resolution");

	full_color = gray;
	if (info->toggle_mode == TOGGLE_FULL)
		full_color = green;
	
	mlx_string_put(info->mlx, info->win, info->text_x,
	info->text_y + 105, gray, "2                        Full Resolution");
	mlx_string_put(info->mlx, info->win, info->text_x,
	info->text_y + 95, full_color, "                _____");
	mlx_string_put(info->mlx, info->win, info->text_x,
	info->text_y + 105, full_color, "               |");
	if (info->toggle_mode == TOGGLE_FULL)
		mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 105, gray, "                 ON");
	else
		mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 105, gray, "                 OFF");
	mlx_string_put(info->mlx, info->win, info->text_x,
	info->text_y + 105, full_color, "                     |");
	mlx_string_put(info->mlx, info->win, info->text_x,
	info->text_y + 105, full_color, "                _____");


	
	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 135, gray, "Pos X Y Z");
	data = ft_itoa(info->scene.camera.coordinates.x);
	mlx_string_put(info->mlx, info->win, info->text_x + 90,
		info->text_y + 135, gray, data);
	data = ft_itoa(info->scene.camera.coordinates.y);
	mlx_string_put(info->mlx, info->win, info->text_x + 120,
		info->text_y + 135, gray, data);
	data = ft_itoa(info->scene.camera.coordinates.z);
	mlx_string_put(info->mlx, info->win, info->text_x + 150,
		info->text_y + 135, gray, data);

	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 155, gray, "Cam X Y Z");
	data = ft_itoa(info->scene.camera.orientation.x * 100);
	mlx_string_put(info->mlx, info->win, info->text_x + 90,
		info->text_y + 155, gray, data);
	data = ft_itoa(info->scene.camera.orientation.y * 100);
	mlx_string_put(info->mlx, info->win, info->text_x + 120,
		info->text_y + 155, gray, data);
	data = ft_itoa(info->scene.camera.orientation.z * 100);
	mlx_string_put(info->mlx, info->win, info->text_x + 150,
		info->text_y + 155, gray, data);
	free (data);
}

int	is_render(t_info *info)
{
	if (info->moving_text ||  info->rotate_camera || info->is_input)
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
