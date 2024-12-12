/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:31:21 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/11 19:17:35 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	multiply_colors(t_color a, t_color b, double factor)
{
	t_color	result;

	result.r = (int)(a.r * b.r * factor / 255.0);
	result.g = (int)(a.g * b.g * factor / 255.0);
	result.b = (int)(a.b * b.b * factor / 255.0);
	return (result);
}

static t_color	add_white_component(t_color base, double factor)
{
	t_color	result;

	result.r = base.r + (int)(255.0 * factor);
	result.g = base.g + (int)(255.0 * factor);
	result.b = base.b + (int)(255.0 * factor);
	return (result);
}

static void	add_diffuse_spec(t_hit_material closest, t_info *info, t_ray ray, t_color *total_diffuse, t_color *total_spec)
{
	int	i;

	i = 0;
	while (i < info->scene.light_n)
	{
		t_light	*light = info->scene.light[i];
		t_vec3 light_dir = vec3_normalize(vec3_sub(light->coordinates, closest.hit_point));
		t_vec3 view_dir = vec3_normalize(vec3_sub(ray.origin, closest.hit_point));
		t_vec3 reflect_dir = vec3_reflect(vec3_mul(light_dir, -1.0), closest.normal);

		double shadow = check_shadow(info, vec3_add(closest.hit_point, vec3_mul(closest.normal, EPSILON)), light->coordinates);

		double diffuse = fmax(0.0, vec3_dot(closest.normal, light_dir)) * closest.diffuse_strength * light->l_brightness * shadow;
		double spec = pow(fmax(0.0, vec3_dot(view_dir, reflect_dir)), closest.shininess) * closest.spec_intensity * shadow;

		t_vec3 to_light = vec3_sub(light->coordinates, closest.hit_point);
		t_color diffuse_color = multiply_colors(closest.base_color, light->color, diffuse);

		t_color specular_color = add_white_component(
				(t_color){0, 0, 0},
				spec * light->l_brightness
				);
		*total_diffuse = t_color_add(*total_diffuse, diffuse_color);
		*total_spec = t_color_add(*total_spec, specular_color);
		i++;
	}
}

/*
	Returns full Phong lights
*/
t_color	add_lights(t_hit_material closest, t_info *info, t_ray ray)
{
	t_color	result;
	t_color	total_diffuse;
	t_color	total_specular;
	t_color	ambient_color;

	total_diffuse.r = 0;
	total_diffuse.g = 0;
	total_diffuse.b = 0;
	total_specular.r = 0;
	total_specular.g = 0;
	total_specular.b = 0;
	ambient_color = multiply_colors(closest.base_color,
			info->scene.ambient.color, info->scene.ambient.a_ratio);
	add_diffuse_spec(closest, info, ray,
		&total_diffuse, &total_specular);
	result.r = ambient_color.r + total_diffuse.r + total_specular.r;
	result.g = ambient_color.g + total_diffuse.g + total_specular.g;
	result.b = ambient_color.b + total_diffuse.b + total_specular.b;
	result = normalize_color(result);
	return (result);
}
