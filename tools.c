/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:49:17 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/11 14:42:23 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	isEqual(double a, double b)
{
	if(fabs(a - b) <= EPSILON * fabs(a))
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
}

void	exit_error(t_scene scene, int free_index_limit, char *message)
{
	int	i;

	i = 0;
	if ((scene.cylinder_n > 0) && scene.cylinder)
	{
		if (scene.cylinder[i])
			free(scene.cylinder[i]);
		i++;
	}
	if (i)
		free (scene.cylinder);
	i = 0;
	if ((scene.sphere_n > 0) && scene.sphere)
	{
		if (scene.sphere[i])
			free(scene.sphere[i]);
		i++;
	}
	if (i)
		free (scene.sphere);
	i = 0;
	if ((scene.plane_n > 0) && scene.plane)
	{
		if (scene.plane[i])
			free(scene.plane[i]);
		i++;
	}
	if (i)
		free (scene.plane);
	i = 0;
	if ((scene.light_n > 0) && scene.light)
	{
		if (scene.light[i])
			free(scene.light[i]);
		i++;
	}
	if (i)
		free (scene.light);
	i = 0;
	if ((scene.cone_n > 0) && scene.cone)
	{
		if (scene.cone[i])
			free(scene.cone[i]);
		i++;
	}
	if (i)
		free (scene.cone);
	ft_putstr_fd(message, 2);
	if (!errno)
	{
		ft_putstr_fd("\n", 2);
		exit (1);
	}
	ft_putstr_fd(": ", 2);
	perror(NULL);
	exit (errno);
}
