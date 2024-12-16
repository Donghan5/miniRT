/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:49:06 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/16 15:12:34 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	toggle_renders(int keycode, t_info *info)
{
	if (keycode == 4)
	{
		info->scene.camera.coordinates.y += 2;
		if (info->toggle_mode == TOGGLE_FULL)
			info->render_type = FULL_RENDER;
		else
			info->render_type = LOW_RENDER;
	}
	else if (keycode == 5)
	{
		info->scene.camera.coordinates.y -= 2;
		if (info->toggle_mode == TOGGLE_FULL)
			info->render_type = FULL_RENDER;
		else
			info->render_type = LOW_RENDER;
	}
}

int	mouse_clicks(int keycode, int x, int y, t_info *info)
{
	if (keycode == 1)
	{
		if (x < info->text_x + 240 && x > info->text_x
			&& y > info->text_y - 15 && y < info->text_y + 200)
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
	else
		toggle_renders(keycode, info);
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
	static double	horiz_cam;
	static double	vertical_cam;
	double			dx;
	double			dy;

	if (info->rotate_camera)
	{
		dx = (x - info->moving_origin_x) * 0.005;
		dy = (y - info->moving_origin_y) * 0.005;
		horiz_cam -= dx;
		vertical_cam = fmax(-M_PI / 2, fmin(M_PI / 2, vertical_cam - dy));
		info->scene.camera.orientation.x = cos(vertical_cam) * sin(horiz_cam);
		info->scene.camera.orientation.y = sin(vertical_cam);
		info->scene.camera.orientation.z = cos(vertical_cam) * cos(horiz_cam);
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
