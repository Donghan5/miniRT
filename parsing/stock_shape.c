/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:19:17 by donghank          #+#    #+#             */
/*   Updated: 2024/12/02 09:23:03 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	stock element of the plane
	@param
		scene: same with stock_ambient()
		info_map: same with stock_ambient()
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
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	scene->plane[pl_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->plane[pl_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->plane[pl_idx]->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split(sep_info[2], ',');
	if (orient_info == NULL)
		handle_error(ORI_ERR);
	scene->plane[pl_idx]->normal_vector.x = ft_atod(orient_info[0]);
	scene->plane[pl_idx]->normal_vector.y = ft_atod(orient_info[1]);
	scene->plane[pl_idx]->normal_vector.z = ft_atod(orient_info[2]);
	free_doub_array(orient_info);
	rgb_infos = ft_split(sep_info[3], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	scene->plane[pl_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->plane[pl_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->plane[pl_idx]->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}

/*
	stock element of stack
	@param
		scene: same with stock_ambient()
		info_map: same with stock_ambient()
		sep_info: same with stock_ambient()
		coord_info: coordination information of sphere
		rgb_infos: RGB information of sphere
*/
void	stock_sphere(t_scene *scene, char *info_map, int sp_idx)
{
	char	**sep_info;
	char	**coord_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	scene->sphere[sp_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->sphere[sp_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->sphere[sp_idx]->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	scene->sphere[sp_idx]->sp_diameter = ft_atod(sep_info[2]);
	rgb_infos = ft_split((char *)sep_info[3], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	scene->sphere[sp_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->sphere[sp_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->sphere[sp_idx]->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}

/*
	stock information of cylinder
	@param
		scene: same with stock_ambient()
		info_map: same with stock_ambient()
		sep_info: same with stock_ambient()
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
	coord_info = ft_split(sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	scene->cylinder[cy_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->cylinder[cy_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->cylinder[cy_idx]->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split((char *)sep_info[2], ',');
	if (orient_info == NULL)
		handle_error(ORI_ERR);
	scene->cylinder[cy_idx]->axis_vector.x = ft_atod(orient_info[0]);
	scene->cylinder[cy_idx]->axis_vector.y = ft_atod(orient_info[1]);
	scene->cylinder[cy_idx]->axis_vector.z = ft_atod(orient_info[2]);
	free_doub_array(orient_info);
	scene->cylinder[cy_idx]->cy_diameter = ft_atod(sep_info[3]);
	scene->cylinder[cy_idx]->cy_height = ft_atod(sep_info[4]);
	rgb_infos = ft_split(sep_info[5], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	scene->cylinder[cy_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->cylinder[cy_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->cylinder[cy_idx]->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}
