/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:01:27 by donghank          #+#    #+#             */
/*   Updated: 2024/12/15 20:16:20 by pzinurov         ###   ########.fr       */
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
		line: information of the map which read by gnl
		sep: separated information
		coord_info: coordinate information of cone
		orient_info: normal vector information of cone
		rgb_infos: RGB information of cone
*/
void	stock_cone(t_scene *scene, char *line, int co_idx)
{
	char	**sep;
	char	**coords;
	char	**orient_info;
	char	**rgb_infos;

	sep = ft_split(line, ' ');
	if (sep == NULL)
		exit_error(line, scene, PARSE_ERR);
	coords = ft_split(sep[1], ',');
	if (coords == NULL)
		return (free_doub_array(sep), exit_error(line, scene, COOR_ERR));
	orient_info = ft_split((char *)sep[2], ',');
	if (orient_info == NULL)
		return (free_doub_array(sep), free_doub_array(coords),
			exit_error(line, scene, ORI_ERR));
	stock_co(scene, coords, orient_info, co_idx);
	free_doub_array(coords);
	free_doub_array(orient_info);
	stock_dia_hei(scene, sep, co_idx);
	rgb_infos = ft_split(sep[5], ',');
	if (rgb_infos == NULL)
		return (free_doub_array(sep), exit_error(line, scene, PARSE_RGB_ERR));
	if (!stock_rgb(&scene->cone[co_idx]->color, rgb_infos))
		return (free_doub_array(sep), exit_error(line, scene, NULL));
	return (free_doub_array(rgb_infos), free_doub_array(sep));
}
