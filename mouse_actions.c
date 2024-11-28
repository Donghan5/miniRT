/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:49:06 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/28 19:28:19 by pzinurov         ###   ########.fr       */
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
		info->moving_map = 1;
	}
	else if (keycode == 3)
	{
		//null
	}
	else if (keycode == 4)
	{
		info->last_scroll_time = get_current_time_ms();
		info->scene.camera.coordinates.y++;
	}
	else if (keycode == 5)
	{
		info->last_scroll_time = get_current_time_ms();
		info->scene.camera.coordinates.y--;
	}
	return (0);
}

int	mouse_off(int keycode, int x, int y, t_info *info)
{
	(void)keycode;
	(void)x;
	(void)y;
	if (info->moving_map)
		info->moving_map = 0;
	if (info->moving_text)
		info->moving_text = 0;
	return (0);
}

int	mouse_moves(int x, int y, t_info *info)
{
	static int	limit_moves;
	static double yaw = 0.0;    // Horizontal rotation
	static double pitch = 0.0;  // Vertical rotation

   if (info->moving_map)
    {
        // Convert mouse movement to angles with reduced sensitivity
        double dx = (x - info->moving_origin_x) * 0.005;  // Horizontal rotation (yaw)
        double dy = (y - info->moving_origin_y) * 0.005;  // Vertical rotation (pitch)

        // Update angles with smoother motion
        yaw -= dx;
        pitch = fmax(-M_PI/2, fmin(M_PI/2, pitch - dy));  // Clamp vertical rotation

        // Convert angles to normalized direction vector (z,y,x order to match convention)
        info->scene.camera.orientation.x = cos(pitch) * sin(yaw);
        info->scene.camera.orientation.y = sin(pitch);
        info->scene.camera.orientation.z = cos(pitch) * cos(yaw);

        // Update origin for next movement
        info->moving_origin_x = x;
        info->moving_origin_y = y;
    }
	else if (info->moving_text)
	{
		info->text_x = x - info->moving_origin_x;
		info->text_y = y - info->moving_origin_y;
	}
	else
		return (0);
	// if (limit_moves--)
	// 	return (0);
	// limit_moves = 7;
	return (0);
}
