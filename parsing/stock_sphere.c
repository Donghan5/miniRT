/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:07:02 by donghank          #+#    #+#             */
/*   Updated: 2024/12/12 16:22:13 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	checking the range of the RGB value
	@param
		rgb_infos: rgb information to free
	@return
		0: out of value (fail)
		1: success
*/
static int	check_range(char **rgb_infos)
{
	if (ft_atoi(rgb_infos[0]) > 255 || \
	ft_atoi(rgb_infos[1]) > 255 || ft_atoi(rgb_infos[2]) > 255)
	{
		return (0);
	}
	return (1);
}

/*
	to stock all information of the coordinate
	@param
		scene: to render
		coord_info: coordinate information
		sp_idx: index of the sphere
*/
static void	stock_coord(t_scene *scene, char **coord_info, int sp_idx)
{
	scene->sphere[sp_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->sphere[sp_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->sphere[sp_idx]->coordinates.z = ft_atod(coord_info[2]);
}

/*
	stock RGB values
	@param
		scene: to render
		rgb_infos: RGB values
		sp_idx: index of sphere_n
*/
static void	stock_rgb(t_scene *scene, char **rgb_infos, int sp_idx)
{
	if (ft_strchr(rgb_infos[0], '.')
		|| ft_strchr(rgb_infos[1], '.')
		|| ft_strchr(rgb_infos[2], '.'))
	{
		free_doub_array(rgb_infos);
		free_just_scene(scene);
		exit_error(NULL, scene, "Invalid rgb value type");
	}
	if (!check_range(rgb_infos))
	{
		free_doub_array(rgb_infos);
		exit_error(NULL, scene, "RGB out of range");
	}
	scene->sphere[sp_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->sphere[sp_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->sphere[sp_idx]->color.b = ft_atoi(rgb_infos[2]);
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
	stock_coord(scene, coord_info, sp_idx);
	free_doub_array(coord_info);
	scene->sphere[sp_idx]->sp_diameter = ft_atod(sep_info[2]);
	rgb_infos = ft_split((char *)sep_info[3], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	stock_rgb(scene, rgb_infos, sp_idx);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}
