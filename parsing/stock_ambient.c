/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:06:48 by donghank          #+#    #+#             */
/*   Updated: 2024/12/15 19:44:17 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	verify the validity of the RGB value
	@param
		scene: to render
		rgb_infos: information of RGB
		sep: separated information
		info: information of the map
*/
static void	verify_rgb(t_scene *scene, char **rgb_infos, char **sep, char *info)
{
	if (ft_strchr(rgb_infos[0], '.')
		|| ft_strchr(rgb_infos[1], '.')
		|| ft_strchr(rgb_infos[2], '.'))
	{
		free_doub_array(rgb_infos);
		free_doub_array(sep);
		exit_error(info, scene, "Invalid rgb value type");
	}
	if (!check_range(rgb_infos))
	{
		free_doub_array(rgb_infos);
		free_doub_array(sep);
		exit_error(info, scene, "Out of range RGB value");
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
		exit_error(info_map, scene, PARSE_ERR);
	scene->ambient.a_ratio = ft_atod(sep_info[1]);
	rgb_infos = ft_split((char *)sep_info[2], ',');
	if (rgb_infos == NULL)
		return (free_doub_array(sep_info), \
			exit_error(NULL, scene, PARSE_RGB_ERR));
	verify_rgb(scene, rgb_infos, sep_info, info_map);
	stock_rgb(scene, rgb_infos);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}
