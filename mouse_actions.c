/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:49:06 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/03 11:49:36 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_clicks(int keycode, int x, int y, t_info *info)
{
	if (keycode == 1)
	{
		if (x < info->text_x + 230 && x > info->text_x
			&& y > info->text_y && y < info->text_y + 100)
		{
			info->moving_origin_x = x - info->text_x;
			info->moving_origin_y = y - info->text_y;
			info->moving_text = 1;
			return (0);
		}
		info->moving_origin_x = x;
		info->moving_origin_y = y;
		info->rotate_camera = 2;
	}
	else if (keycode == 3)
	{
		info->moving_origin_x = x;
		info->moving_origin_y = y;
		info->rotate_camera = 1;
	}
	else if (keycode == 4)
	{
		info->scene.camera.coordinates.y++;
		if (info->toggle_mode == TOGGLE_FULL)
			info->render_type = FULL_RENDER;
		else
			info->render_type = LOW_RENDER;
	}
	else if (keycode == 5)
	{
		info->scene.camera.coordinates.y--;
		if (info->toggle_mode == TOGGLE_FULL)
			info->render_type = FULL_RENDER;
		else
			info->render_type = LOW_RENDER;
	}
	return (0);
}

int	mouse_off(int keycode, int x, int y, t_info *info)
{
	(void)keycode;
	(void)x;
	(void)y;
	if (info->rotate_camera)
		info->rotate_camera = 0;
	if (info->moving_text)
		info->moving_text = 0;
	return (0);
}

int	mouse_moves(int x, int y, t_info *info)
{
	static int		limit_moves;
	static double	yaw;
	static double	pitch;
	double			dx;
	double			dy;

	if (info->rotate_camera)
	{
		dx = (x - info->moving_origin_x) * 0.005;
		dy = (y - info->moving_origin_y) * 0.005;

		yaw -= dx;
		pitch = fmax(-M_PI/2, fmin(M_PI/2, pitch - dy));

		info->scene.camera.orientation.x = cos(pitch) * sin(yaw);
		info->scene.camera.orientation.y = sin(pitch);
		info->scene.camera.orientation.z = cos(pitch) * cos(yaw);

		info->moving_origin_x = x;
		info->moving_origin_y = y;
	}
	else if (info->moving_text)
	{
		info->text_x = x - info->moving_origin_x;
		info->text_y = y - info->moving_origin_y;
	}
	return (0);
}
