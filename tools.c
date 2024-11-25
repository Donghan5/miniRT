/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:49:17 by pzinurov          #+#    #+#             */
/*   Updated: 2024/11/25 20:48:58 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
