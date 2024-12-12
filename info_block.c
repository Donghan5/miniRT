/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:22:23 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/11 18:26:23 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_low_res(t_info *info, unsigned int gray, unsigned int green)
{
	unsigned int	low_color;

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
}

static void	print_full_res(t_info *info, unsigned int gray, unsigned int green)
{
	unsigned int	full_color;

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
}

static void	print_camera_coord(t_info *info, unsigned int gray)
{
	char	*data;

	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 135, gray, "Pos X Y Z");
	data = ft_itoa(info->scene.camera.coordinates.x);
	mlx_string_put(info->mlx, info->win, info->text_x + 90,
		info->text_y + 135, gray, data);
	free(data);
	data = ft_itoa(info->scene.camera.coordinates.y);
	mlx_string_put(info->mlx, info->win, info->text_x + 120,
		info->text_y + 135, gray, data);
	free(data);
	data = ft_itoa(info->scene.camera.coordinates.z);
	mlx_string_put(info->mlx, info->win, info->text_x + 150,
		info->text_y + 135, gray, data);
	free(data);
}

void	print_camera_view(t_info *info, unsigned int gray)
{
	char	*data;

	mlx_string_put(info->mlx, info->win, info->text_x,
		info->text_y + 155, gray, "Cam X Y Z");
	data = ft_itoa(info->scene.camera.orientation.x * 100);
	mlx_string_put(info->mlx, info->win, info->text_x + 90,
		info->text_y + 155, gray, data);
	free(data);
	data = ft_itoa(info->scene.camera.orientation.y * 100);
	mlx_string_put(info->mlx, info->win, info->text_x + 120,
		info->text_y + 155, gray, data);
	free(data);
	data = ft_itoa(info->scene.camera.orientation.z * 100);
	mlx_string_put(info->mlx, info->win, info->text_x + 150,
		info->text_y + 155, gray, data);
	free (data);
}

void	print_info_block(t_info *info)
{
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
	print_low_res(info, gray, green);
	print_full_res(info, gray, green);
	print_camera_coord(info, gray);
	print_camera_view(info, gray);
}
