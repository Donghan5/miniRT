/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:39:04 by donghank          #+#    #+#             */
/*   Updated: 2024/12/09 15:03:11 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	checking the range of the RGB value
	@param
		rgb_infos: rgb information to free
*/
static void	check_range(char **rgb_infos)
{
	if (ft_atoi(rgb_infos[0]) > 255 || ft_atoi(rgb_infos[1]) > 255 || ft_atoi(rgb_infos[2]) > 255)
	{
		free_doub_array(rgb_infos);
		handle_error("RGB value, out of range");
		printf("Is it working check_range");
	}
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
static void	stock_coord_orient(t_scene *scene, char **coord_info, char **orient_info, int cy_idx)
{
	scene->cylinder[cy_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->cylinder[cy_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->cylinder[cy_idx]->coordinates.z = ft_atod(coord_info[2]);
	scene->cylinder[cy_idx]->axis_vector.x = ft_atod(orient_info[0]);
	scene->cylinder[cy_idx]->axis_vector.y = ft_atod(orient_info[1]);
	scene->cylinder[cy_idx]->axis_vector.z = ft_atod(orient_info[2]);
}

/*
	helper funtion to stock rgb value
	helper function of diameter and height
	@param
		scene: scene to render
		rgb_infos: information of RGB value
		cy_idx: index of the cylinder
*/
static void	stock_rgb(t_scene *scene, char **rgb_infos, int cy_idx)
{
	if (ft_strchr(rgb_infos[0], '.')|| ft_strchr(rgb_infos[1], '.')|| ft_strchr(rgb_infos[2], '.'))
	{
		free_doub_array(rgb_infos);
		handle_error("Invalid rgb value type");
	}
	check_range(rgb_infos);
	scene->cylinder[cy_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->cylinder[cy_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->cylinder[cy_idx]->color.b = ft_atoi(rgb_infos[2]);
}

/*
	helper function of diameter and height
	@param
		scene: to render
		sep_info: separated information
		cy_idx: index of the cylinder
*/
static void	stock_dia_hei(t_scene *scene, char **sep_info, int cy_idx)
{
	scene->cylinder[cy_idx]->cy_diameter = ft_atod(sep_info[3]);
	scene->cylinder[cy_idx]->cy_height = ft_atod(sep_info[4]);
}

/*
	stock information of cylinder
	@param
		scene: scene to render
		info_map: information of the map which read by gnl
		sep_info: separated information
		coord_info: coordinate information of cylinder
		orient_info: normal vector information of cylinder
		rgb_infos: RGB information of cylinder
*/
void	stock_cylinder(t_scene *scene, char *info_map, int cy_idx)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	// valid_form(sep_info);
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	orient_info = ft_split((char *)sep_info[2], ',');
	if (orient_info == NULL)
		handle_error(ORI_ERR);
	stock_coord_orient(scene, coord_info, orient_info, cy_idx);
	free_doub_array(coord_info);
	free_doub_array(orient_info);
	stock_dia_hei(scene, sep_info, cy_idx);
	rgb_infos = ft_split(sep_info[5], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	stock_rgb(scene, rgb_infos, cy_idx);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}
