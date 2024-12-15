/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 23:07:02 by donghank          #+#    #+#             */
/*   Updated: 2024/12/15 19:38:58 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	stock coordinate informations
	@param
		scene: to render
		coord_info: information of the coordinate
		sp_idx: index of the sphere
*/
static void	stock_coord(t_scene *scene, char **coord_info, int sp_idx)
{
	scene->sphere[sp_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->sphere[sp_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->sphere[sp_idx]->coordinates.z = ft_atod(coord_info[2]);
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
	stock RGB values
	@param
		scene: to render
		rgb_infos: RGB values
		sp_idx: index of sphere_n
*/
static void	stock_rgb(t_scene *scene, char **rgb_infos, int sp_idx)
{
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
void	stock_sphere(t_scene *scene, char *info, int sp_idx)
{
	char	**sep;
	char	**coord_info;
	char	**rgb_infos;

	sep = ft_split(info, ' ');
	if (sep == NULL)
		handle_error(PARSE_ERR);
	coord_info = ft_split(sep[1], ',');
	if (coord_info == NULL)
		return (free_doub_array(sep), exit_error(info, scene, COOR_ERR));
	stock_coord(scene, coord_info, sp_idx);
	free_doub_array(coord_info);
	scene->sphere[sp_idx]->sp_diameter = ft_atod(sep[2]);
	rgb_infos = ft_split((char *)sep[3], ',');
	if (rgb_infos == NULL)
		return (free_doub_array(sep), exit_error(info, scene, PARSE_RGB_ERR));
	verify_rgb(scene, rgb_infos, sep, info);
	stock_rgb(scene, rgb_infos, sp_idx);
	free_doub_array(rgb_infos);
	free_doub_array(sep);
}
