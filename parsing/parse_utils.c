/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:06:16 by donghank          #+#    #+#             */
/*   Updated: 2024/12/15 19:49:50 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	check the space
	@param
		c: checking char
*/
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r');
}

/*
	check the all case of the empty and comment
	@param
		line: to verify line read by gnl
	@return
		1: success
		0: fail (there's comment or line)
*/
int	is_empty_or_comment(char *line)
{
	if (line == NULL || *line == '\0')
		return (1);
	while (*line)
	{
		if (!ft_isspace(*line))
		{
			if (*line == '#')
				return (1);
			return (0);
		}
		line++;
	}
	return (1);
}

/*
	@param
		msg: error msg
*/
void	handle_error(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
