/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:16:25 by donghank          #+#    #+#             */
/*   Updated: 2024/12/04 22:28:52 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		handle_error(PARSE_ERR);
	scene->ambient.a_ratio = ft_atod(sep_info[1]);
	rgb_infos = ft_split((char *)sep_info[2], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	scene->ambient.color.r = ft_atoi(rgb_infos[0]);
	scene->ambient.color.g = ft_atoi(rgb_infos[1]);
	scene->ambient.color.b = ft_atoi(rgb_infos[2]);
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
	stock the informations of camera
	@param
		scene: same with stock_ambient
		info_map: same with stock_ambient
		sep_info: same with stock_ambient
		coord_info: coordination information of camera
		orient_info: orientation vector information of camera

*/
void	stock_cam(t_scene *scene, char *info_map)
{
	char	**sep_info;
	char	**coord_info;
	char	**orient_info;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	coord_info = ft_split((char *)sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	scene->camera.coordinates.x = ft_atod(coord_info[0]);
	scene->camera.coordinates.y = ft_atoi(coord_info[1]);
	scene->camera.coordinates.z = ft_atoi(coord_info[2]);
	free_doub_array(coord_info);
	orient_info = ft_split((char *)sep_info[2], ',');
	if (orient_info == NULL)
		handle_error(ORI_ERR);
	scene->camera.orientation.x = ft_atod(orient_info[0]);
	scene->camera.orientation.y = ft_atod(orient_info[1]);
	scene->camera.orientation.z = ft_atod(orient_info[2]);
	scene->camera.c_view = ft_atod(sep_info[3]);
	free_doub_array(orient_info);
	free_doub_array(sep_info);
}

/*
	stock function
	@param
		scene: same with function stock_ambient
		info_map: same with function stock_ambient
		sep_info: same with function stock_ambient
		coord_info: coordinate information of light
		rgb_infos: RGB information of light

*/
void	stock_light(t_scene *scene, char *info_map, int l_idx)
{
	char	**sep_info;
	char	**coord_info;
	char	**rgb_infos;

	sep_info = ft_split(info_map, ' ');
	if (sep_info == NULL)
		handle_error(PARSE_ERR);
	coord_info = ft_split((char *)sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	scene->light[l_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->light[l_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->light[l_idx]->coordinates.z = ft_atod(coord_info[2]);
	free_doub_array(coord_info);
	scene->light[l_idx]->l_brightness = ft_atod(sep_info[2]);
	rgb_infos = ft_split((char *)sep_info[3], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	scene->light[l_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->light[l_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->light[l_idx]->color.b = ft_atoi(rgb_infos[2]);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}


/*
	part of ambient, camera
	@param
		type: type of the map_infos[1]
		scene: structure to stock the infos
		info_map: numeric information of the map
*/
void	stock_infos(int type, t_scene *scene, char *info_map)
{
	if (type == 1)
		stock_ambient(scene, info_map);
	else if (type == 2)
		stock_cam(scene, info_map);
}
