/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:16:25 by donghank          #+#    #+#             */
/*   Updated: 2024/12/06 00:48:59 by donghank         ###   ########.fr       */
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
