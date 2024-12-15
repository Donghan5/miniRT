/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:01:27 by donghank          #+#    #+#             */
/*   Updated: 2024/12/15 01:18:15 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	checking the range of the RGB value
	@param
		rgb_infos: rgb information to free
	@return
		1: success
		0: fail
*/
static int	check_range(char **rgb_infos)
{
	if (ft_atoi(rgb_infos[0]) > 255
		|| ft_atoi(rgb_infos[1]) > 255
		|| ft_atoi(rgb_infos[2]) > 255)
		return (0);
	return (1);
}

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
	helper funtion to stock rgb value

	@param
		scene: scene to render
		rgb_infos: information of RGB value
		cy_idx: index of the cylinder
*/
static void	stock_rgb(t_scene *scene, char **rgb_infos, int co_idx)
{
	if (ft_strchr(rgb_infos[0], '.')
		|| ft_strchr(rgb_infos[1], '.')
		|| ft_strchr(rgb_infos[2], '.'))
	{
		free_doub_array(rgb_infos);
		exit_error(NULL, scene, "Invalid rgb value type");
	}
	if (!check_range(rgb_infos))
	{
		free_doub_array(rgb_infos);
		exit_error(NULL, scene, "Out of range RGB value");
	}
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
void	stock_cone(t_scene *scene, char *info_map, int co_idx)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		exit_error(info_map, scene, PARSE_ERR);
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		exit_error(info_map, scene, COOR_ERR);
	orient_info = ft_split((char *)sep_info[2], ',');
	if (orient_info == NULL)
		exit_error(info_map, scene, ORI_ERR);
	stock_co(scene, coord_info, orient_info, co_idx);
	free_doub_array(coord_info);
	free_doub_array(orient_info);
	stock_dia_hei(scene, sep_info, co_idx);
	rgb_infos = ft_split(sep_info[5], ',');
	if (rgb_infos == NULL)
		exit_error(info_map, scene, PARSE_RGB_ERR);
	stock_rgb(scene, rgb_infos, co_idx);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}
