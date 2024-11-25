/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:50:09 by donghank          #+#    #+#             */
/*   Updated: 2024/11/25 13:50:10 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	helper function of atod
	check of the sign (positive and negative)
*/
static void	check_sign(const char **str, int *sign)
{
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign = -1;
		*str++;
	}
}

/*
	convert char * to double (aim to stock the info)
*/
double	ft_atod(const char *str)
{
	double	res;
	double	fraction;
	double	div;
	int		sign;

	sign = 1;
	res = 0.0;
	fraction = 0.0;
	div = 1.0;
	while (*str == ' ')
		str++;
	check_sign(&str, &sign);
	while (ft_isdigit(*str))
		res = res * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			fraction = fraction * 10.0 + (*str++ - '0');
			div *= 10.0;
		}
	}
	res += fraction / div;
	return (sign * res);
}
