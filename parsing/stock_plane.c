/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:30:21 by donghank          #+#    #+#             */
/*   Updated: 2024/12/10 15:50:27 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	helper function to stock information of coordinate
	@param
		scene: scene to render
		coord_info: information of coordination(x, y, z)
		pl_idx: index of plane
*/
static void	stock_coordinate(t_scene *scene, char **coord_info, int pl_idx)
{
	scene->plane[pl_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->plane[pl_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->plane[pl_idx]->coordinates.z = ft_atod(coord_info[2]);
}

/*
	helper function to stock the normal vector
	@param
		scene: scene to render
		orient_info: information of the normal vector
		pl_idx: index of plane
*/
static void	stock_normal_vec(t_scene *scene, char **orient_info, int pl_idx)
{
	scene->plane[pl_idx]->normal_vector.x = ft_atod(orient_info[0]);
	scene->plane[pl_idx]->normal_vector.y = ft_atod(orient_info[1]);
	scene->plane[pl_idx]->normal_vector.z = ft_atod(orient_info[2]);
}

/*
	helper function to stock the value of rgb
	@param
		scene: scene to render
		rgb_infos: rgb information
		pl_idx: index of plane
*/
static void	stock_rgb(t_scene *scene, char **rgb_infos, int pl_idx)
{
	scene->plane[pl_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->plane[pl_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->plane[pl_idx]->color.b = ft_atoi(rgb_infos[2]);
}

/*
	stock element of the plane
	@param
		scene: scene to render
		info_map: information of the map which read by gnl
		sep_info: separated information
		coord_info: coordination information of plane
		orient_info: normal vector information of plane
		rgb_infos: RGB information of plane

*/
void	stock_plane(t_scene *scene, char *info_map, int pl_idx)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	valid_form(4, sep_info);
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	stock_coordinate(scene, coord_info, pl_idx);
	free_doub_array(coord_info);
	orient_info = ft_split(sep_info[2], ',');
	if (orient_info == NULL)
		handle_error(ORI_ERR);
	stock_normal_vec(scene, orient_info, pl_idx);
	free_doub_array(orient_info);
	rgb_infos = ft_split(sep_info[3], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	stock_rgb(scene, rgb_infos, pl_idx);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}
