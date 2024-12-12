/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pzinurov <pzinurov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:49:17 by pzinurov          #+#    #+#             */
/*   Updated: 2024/12/11 16:31:24 by pzinurov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_equal(double a, double b)
{
	if (fabs(a - b) <= EPSILON * fabs(a))
		return (1);
	return (0);
}

void	smart_free(void *element)
{
	if (element != NULL)
		free(element);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
}

void	exit_error(char *line, t_scene *scene, char *message)
{
	smart_free(line);
	if (scene)
		free_scene_safe(scene);
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

void	free_scene_safe(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->cylinder_n || i < scene->sphere_n
		|| i < scene->plane_n || i < scene->light_n
		|| i < scene->cone_n)
	{
		if (i < scene->cylinder_n && scene->cylinder)
			smart_free(scene->cylinder[i]);
		if (i < scene->sphere_n && scene->sphere)
			smart_free(scene->sphere[i]);
		if (i < scene->plane_n && scene->plane)
			smart_free(scene->plane[i]);
		if (i < scene->light_n && scene->light)
			smart_free(scene->light[i]);
		if (i < scene->cone_n && scene->cone)
			smart_free(scene->cone[i]);
		i++;
	}
	smart_free(scene->cylinder);
	smart_free(scene->sphere);
	smart_free(scene->plane);
	smart_free(scene->light);
	smart_free(scene->cone);
}
