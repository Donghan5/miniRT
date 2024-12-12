/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:06:48 by donghank          #+#    #+#             */
/*   Updated: 2024/12/12 16:21:22 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	checking the range of the RGB value
	@param
		rgb_infos: rgb information to free
*/
static void	check_range(char **rgb_infos, t_scene *scene)
{
	if (ft_atoi(rgb_infos[0]) > 255
		|| ft_atoi(rgb_infos[1]) > 255
		|| ft_atoi(rgb_infos[2]) > 255)
	{
		free_doub_array(rgb_infos);
		exit_error(NULL, scene, "RGB value, out of range");
		printf("Is it working check_range");
	}
}

/*
	stock the rgb value and check int or double
	@param
		scene: to render
		rgb_infos: information of RGB
*/
static void	stock_rgb(t_scene *scene, char **rgb_infos)
{
	if (ft_strchr(rgb_infos[0], '.')
		|| ft_strchr(rgb_infos[1], '.')
		|| ft_strchr(rgb_infos[2], '.'))
	{
		free_doub_array(rgb_infos);
		exit_error(NULL, scene, "Invalid rgb value type");
	}
	check_range(rgb_infos, scene);
	scene->ambient.color.r = ft_atoi(rgb_infos[0]);
	scene->ambient.color.g = ft_atoi(rgb_infos[1]);
	scene->ambient.color.b = ft_atoi(rgb_infos[2]);
}

/*
	stock functions
	using ft_atod convert
	@param
		scene: structure of scene (to print with mlx)
		info_map: information of the map which read by gnl
		sep_info: separate information of info_map
		rgb_infos: RGB information

*/
void	stock_ambient(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		exit_error(NULL, scene, PARSE_ERR);
	// valid_form_amb(sep_info);
	scene->ambient.a_ratio = ft_atod(sep_info[1]);
	rgb_infos = ft_split((char *)sep_info[2], ',');
	if (rgb_infos == NULL)
		exit_error(NULL, scene, PARSE_RGB_ERR);
	stock_rgb(scene, rgb_infos);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}
