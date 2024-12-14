/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:48:43 by donghank          #+#    #+#             */
/*   Updated: 2024/12/12 21:13:01 by donghank         ###   ########.fr       */
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
	stock coordinate information
	@param
		scene: to render
		coord_info: information of coordinate
		l_idx: index of light_n
*/
static void	stock_coord(t_scene *scene, char **coord_info, int l_idx)
{
	scene->light[l_idx]->coordinates.x = ft_atod(coord_info[0]);
	scene->light[l_idx]->coordinates.y = ft_atod(coord_info[1]);
	scene->light[l_idx]->coordinates.z = ft_atod(coord_info[2]);
}

/*
	stock RGB information
	@param
		scene: to render
		rgb_infos: RGB information
		l_idx: index of light_n
*/
static void	stock_rgb(t_scene *scene, char **rgb_infos, int l_idx)
{
	if (ft_strchr(rgb_infos[0], '.')|| ft_strchr(rgb_infos[1], '.')|| ft_strchr(rgb_infos[2], '.'))
	{
		free_doub_array(rgb_infos);
		exit_error(NULL, scene, "Invalid rgb value type");
	}
	if (!check_range(rgb_infos))
	{
		free_doub_array(rgb_infos);
		exit_error(NULL, scene, "RGB value out of range");
	}
	scene->light[l_idx]->color.r = ft_atoi(rgb_infos[0]);
	scene->light[l_idx]->color.g = ft_atoi(rgb_infos[1]);
	scene->light[l_idx]->color.b = ft_atoi(rgb_infos[2]);
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
		exit_error(info_map, scene, PARSE_ERR);
	// valid_form(sep_info);
	coord_info = ft_split((char *)sep_info[1], ',');
	if (coord_info == NULL)
		return (free_doub_array(sep_info),
			exit_error(info_map, scene, COOR_ERR));
	stock_coord(scene, coord_info, l_idx);
	free_doub_array(coord_info);
	scene->light[l_idx]->l_brightness = ft_atod(sep_info[2]);
	rgb_infos = ft_split((char *)sep_info[3], ',');
	if (rgb_infos == NULL)
		return (free_doub_array(sep_info),
			exit_error(info_map, scene, PARSE_RGB_ERR));
	stock_rgb(scene, rgb_infos, l_idx);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}
