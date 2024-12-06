/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:07:02 by donghank          #+#    #+#             */
/*   Updated: 2024/12/06 00:57:39 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void stock_coord(t_scene *scene, char **coord_info, int sp_idx)
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
	if (ft_strncmp(rgb_infos[0], ".", 1) == 0 || ft_strncmp(rgb_infos[1], ".", 1) == 0 || ft_strncmp(rgb_infos[2], ".", 1) == 0)
	{
		free_doub_array(rgb_infos);
		handle_error("Invalid rgb value type");
		return ;
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
