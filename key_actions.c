/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:48:58 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/10 13:57:37 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	apply_movement(t_info *info, double forward, double sideways)
{
	double	yaw;

	if (info->rotate_camera == 1)
	{
		if (forward > 0)
			info->scene.camera.coordinates.z++;
		else if (forward < 0)
			info->scene.camera.coordinates.z--;
		else if (sideways > 0)
			info->scene.camera.coordinates.x++;
		else if (sideways < 0)
			info->scene.camera.coordinates.x--;
		return ;
	}
	yaw = atan2(info->scene.camera.orientation.x,
			info->scene.camera.orientation.z);
	if (forward != 0 && sideways != 0)
	{
		forward *= 0.7071067811865476;
		sideways *= 0.7071067811865476;
	}
	if (forward != 0)
	{
		info->scene.camera.coordinates.x += forward * sin(yaw);
		info->scene.camera.coordinates.z += forward * cos(yaw);
	}
	if (sideways != 0)
	{
		info->scene.camera.coordinates.x += sideways * sin(yaw + M_PI / 2);
		info->scene.camera.coordinates.z += sideways * cos(yaw + M_PI / 2);
	}
}

static void	update_key_states(t_info *info, t_key_state *keys, int keycode, int is_pressed)
{
	if (is_pressed)
	{
		if (keycode == 65361 || keycode == 97)
			keys->left = 1;
		else if (keycode == 65363 || keycode == 100)
			keys->right = 1;
		else if (keycode == 65362 || keycode == 119)
			keys->forward = 1;
		else if (keycode == 65364 || keycode == 115)
			keys->backward = 1;
	}
	else
	{
		if (keycode == 65361 || keycode == 97)
			keys->left = 0;
		else if (keycode == 65363 || keycode == 100)
			keys->right = 0;
		else if (keycode == 65362 || keycode == 119)
			keys->forward = 0;
		else if (keycode == 65364 || keycode == 115)
			keys->backward = 0;
		if (!keys->left && !keys->backward && !keys->forward && !keys->right)
			info->is_input = 0;
	}
}

static void update_movement(t_info *info, int keycode, int is_pressed)
{
    double	forward;
    double	sideways;
	static t_key_state	keys;

	forward = 0;
	sideways = 0;
	update_key_states(info, &keys, keycode, is_pressed);
    if (keys.forward)
        forward += 2.0;
    if (keys.backward)
        forward -= 2.0;
    if (keys.right)
        sideways -= 2.0;
    if (keys.left)
        sideways += 2.0;
    if (forward != 0 || sideways != 0)
	{
        info->is_input = 1;
        apply_movement(info, forward, sideways);
    }
}

static void simple_key_actions(int keycode, t_info *info)
{
	if (keycode == 49 && info->toggle_mode != TOGGLE_LOW)
	{
		info->render_type = LOW_RENDER;
		info->toggle_mode = TOGGLE_LOW;
	}
	else if (keycode == 50 && info->toggle_mode != TOGGLE_FULL)
	{
		info->render_type = FULL_RENDER;
		info->toggle_mode = TOGGLE_FULL;
	}
	else if (keycode == 49)
	{
		info->render_type = FULL_RENDER;
		info->toggle_mode = TOGGLE_OFF;
	}
	else if (keycode == 50)
	{
		info->render_type = LOW_RENDER;
		info->toggle_mode = TOGGLE_OFF;
	}
}

int key_pressed(int keycode, t_info *info)
{
    if (keycode == 65307 || keycode == 113)
        close_window(info);
    else
	{
        simple_key_actions(keycode, info);
		update_movement(info, keycode, 1);
	}
    return (0);
}

int key_off(int keycode, t_info *info)
{
    update_movement(info, keycode, 0);
    return (0);
}
