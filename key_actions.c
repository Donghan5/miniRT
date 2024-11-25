/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:48:58 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/25 21:14:58 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

// Key state tracking
typedef struct s_key_state {
    int forward;     // W
    int backward;    // S
    int left;        // A
    int right;       // D
}				t_key_state;

static t_key_state keys = {0, 0, 0, 0};

static void apply_movement(t_info *info, double forward, double sideways)
{
    // Get directional vector from camera orientation angles
    double yaw = atan2(info->scene.camera.orientation.x, info->scene.camera.orientation.z);
    
    // Apply diagonal normalization if moving in both directions
    if (forward != 0 && sideways != 0) {
        // Normalize diagonal movement
        const double DIAGONAL_SCALE = 0.7071067811865476; // 1/sqrt(2)
        forward *= DIAGONAL_SCALE;
        sideways *= DIAGONAL_SCALE;
    }

    // Calculate movement vector based on yaw angle
    if (forward != 0) {
        info->scene.camera.coordinates.x += forward * sin(yaw);
        info->scene.camera.coordinates.z += forward * cos(yaw);
    }
    
    if (sideways != 0) {
        // For sideways movement, add 90 degrees (PI/2) to yaw
        info->scene.camera.coordinates.x += sideways * sin(yaw + M_PI/2);
        info->scene.camera.coordinates.z += sideways * cos(yaw + M_PI/2);
    }
}

static void update_movement(t_info *info)
{
    const double MOVE_SPEED = 2.0;
    double forward = 0;
    double sideways = 0;

    // Calculate total movement based on active keys
    if (keys.forward)
        forward += MOVE_SPEED;
    if (keys.backward)
        forward -= MOVE_SPEED;
    if (keys.right)
        sideways -= MOVE_SPEED;
    if (keys.left)
        sideways += MOVE_SPEED;

    // Only apply movement if there's any movement to apply
    if (forward != 0 || sideways != 0) {
        info->is_input = 1;
        apply_movement(info, forward, sideways);
    }
}

static void simple_key_actions(int keycode, t_info *info)
{
    if (keycode == 65361 || keycode == 97)  // Left arrow or A
        keys.left = 1;
    else if (keycode == 65363 || keycode == 100)  // Right arrow or D
        keys.right = 1;
    else if (keycode == 65362 || keycode == 119)  // Up arrow or W
        keys.forward = 1;
    else if (keycode == 65364 || keycode == 115)  // Down arrow or S
        keys.backward = 1;
    update_movement(info);
}

int key_pressed(int keycode, t_info *info)
{
    if (keycode == 65307 || keycode == 113)
        close_window(info);
    else
        simple_key_actions(keycode, info);
    return (0);
}

int key_off(int keycode, t_info *info)
{
    // Update key states on release
    if (keycode == 65361 || keycode == 97)  // Left arrow or A
        keys.left = 0;
    if (keycode == 65363 || keycode == 100)  // Right arrow or D
        keys.right = 0;
    if (keycode == 65362 || keycode == 119)  // Up arrow or W
        keys.forward = 0;
    if (keycode == 65364 || keycode == 115)  // Down arrow or S
        keys.backward = 0;

	if (!keys.left && !keys.backward && !keys.forward && !keys.right)
		info->is_input = 0;
	else
    	update_movement(info);
    return (0);
}
