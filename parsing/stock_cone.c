/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:01:27 by donghank          #+#    #+#             */
/*   Updated: 2024/12/15 19:45:14 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	helper function of stock coordinate
	helper function of stock axis vector
	@param
		scene: scene to render
		coord_info: information of the coordinate (x, y, z)
		orient_info: information of axis vector
		cy_idx: index of cylinder
*/
static void	stock_co(t_scene *scene, char **coord_info, \
					char **orient_info, int co_idx)
{
	scene->cone[co_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->cone[co_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->cone[co_idx]->coordinates.z = ft_atod(coord_info[2]);
	scene->cone[co_idx]->axis_vector.x = ft_atod(orient_info[0]);
	scene->cone[co_idx]->axis_vector.y = ft_atod(orient_info[1]);
	scene->cone[co_idx]->axis_vector.z = ft_atod(orient_info[2]);
}

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
	helper funtion to stock rgb value

	@param
		scene: scene to render
		rgb_infos: information of RGB value
		co_idx: index of the cylinder
*/
static void	stock_rgb(t_scene *scene, char **rgb_infos, int co_idx)
{
	scene->cone[co_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->cone[co_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->cone[co_idx]->color.b = ft_atoi(rgb_infos[2]);
}

/*
	helper function of diameter and height
	@param
		scene: to render
		sep_info: separated information
		co_idx: index of the cone
*/
static void	stock_dia_hei(t_scene *scene, char **sep_info, int co_idx)
{
	scene->cone[co_idx]->co_diameter = ft_atod(sep_info[3]);
	scene->cone[co_idx]->co_height = ft_atod(sep_info[4]);
}

/*
	stock information of cone
	@param
		scene: scene to render
		info_map: information of the map which read by gnl
		sep_info: separated information
		coord_info: coordinate information of cone
		orient_info: normal vector information of cone
		rgb_infos: RGB information of cone
*/
void	stock_cone(t_scene *scene, char *info, int co_idx)
{
	char	**sep;
	char	**coord_info;
	char	**orient_info;
	char	**rgb_infos;

	sep = ft_split(info, ' ');
	if (sep == NULL)
		exit_error(info, scene, PARSE_ERR);
	coord_info = ft_split(sep[1], ',');
	if (coord_info == NULL)
		return (free_doub_array(sep), exit_error(info, scene, COOR_ERR));
	orient_info = ft_split((char *)sep[2], ',');
	if (orient_info == NULL)
		return (free_doub_array(sep), exit_error(info, scene, ORI_ERR));
	stock_co(scene, coord_info, orient_info, co_idx);
	free_doub_array(coord_info);
	free_doub_array(orient_info);
	stock_dia_hei(scene, sep, co_idx);
	rgb_infos = ft_split(sep[5], ',');
	if (rgb_infos == NULL)
		return (free_doub_array(sep), exit_error(info, scene, PARSE_RGB_ERR));
	verify_rgb(scene, rgb_infos, sep, info);
	stock_rgb(scene, rgb_infos, co_idx);
	free_doub_array(rgb_infos);
	free_doub_array(sep);
}
