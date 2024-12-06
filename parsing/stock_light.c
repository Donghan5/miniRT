/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 00:48:43 by donghank          #+#    #+#             */
/*   Updated: 2024/12/06 01:25:09 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (ft_strncmp(rgb_infos[0], ".", 1) == 0 || ft_strncmp(rgb_infos[1], ".", 1) == 0 || ft_strncmp(rgb_infos[2], ".", 1) == 0)
	{
		free_doub_array(rgb_infos);
		handle_error("Invalid rgb value type");
		return ;
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
		handle_error(PARSE_ERR);
	coord_info = ft_split((char *)sep_info[1], ',');
	if (coord_info == NULL)
		handle_error(COOR_ERR);
	stock_coord(scene, coord_info, l_idx);
	free_doub_array(coord_info);
	scene->light[l_idx]->l_brightness = ft_atod(sep_info[2]);
	rgb_infos = ft_split((char *)sep_info[3], ',');
	if (rgb_infos == NULL)
		handle_error(PARSE_RGB_ERR);
	stock_rgb(scene, rgb_infos, l_idx);
	free_doub_array(rgb_infos);
	free_doub_array(sep_info);
}
