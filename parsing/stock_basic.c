/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:16:25 by donghank          #+#    #+#             */
/*   Updated: 2024/12/15 21:17:45 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

// t_bool	stock_rgb(t_color *color, char **rgb_infos)
// {
// 	if (ft_strchr(rgb_infos[0], '.')
// 		|| ft_strchr(rgb_infos[1], '.')
// 		|| ft_strchr(rgb_infos[2], '.'))
// 	{
// 		free_doub_array(rgb_infos);
// 		ft_putstr_fd("Error\nInvalid rgb value type\n", 2);
// 		return (0);
// 	}
// 	if (!check_range(rgb_infos))
// 	{
// 		free_doub_array(rgb_infos);
// 		ft_putstr_fd("Error\nRGB value out of range\n", 2);
// 		return (0);
// 	}
// 	(*color).r = ft_atoi(rgb_infos[0]);
// 	(*color).g = ft_atoi(rgb_infos[1]);
// 	(*color).b = ft_atoi(rgb_infos[2]);
// 	return (1);
// }

/*
	checking the range of the RGB value
	@param
		rgb_infos: rgb information to free
	@return
		1: success
		0: fail
*/
int	check_range(char **rgb_infos)
{
	if (ft_atoi(rgb_infos[0]) > 255
		|| ft_atoi(rgb_infos[1]) > 255
		|| ft_atoi(rgb_infos[2]) > 255)
		return (0);
	return (1);
}
