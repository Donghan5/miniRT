/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghank <donghank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:54:06 by donghank          #+#    #+#             */
/*   Updated: 2024/12/12 12:57:57 by donghank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// A    double    int, int, int
void	validity_type_one(char *map_info, size_t *i)
{
	check_doub(map_info, i);
	check_three(map_info, i, "int");
}

// C    int, int, int    double, double, double    int
void	validity_type_two(char *map_info, size_t *i)
{
	check_three(map_info, i, "int");
	check_three(map_info, i, "double");
	check_int(map_info, i);
}

// [L, sp]   double, double, double    double    int, int, int
void	validity_type_three(char *map_info, size_t *i)
{
	check_three(map_info, i, "double");
	check_doub(map_info, i);
	check_three(map_info, i, "int");
}

// pl    double, double, double    double, double, double    int, int, int
void	validity_type_four(char *map_info, size_t *i)
{
	check_three(map_info, i, "double");
	check_three(map_info, i, "double");
	check_three(map_info, i, "int");
}

// [cy, co]    double, double, double    double, double, double
//			   double    double    int, int, int
void	validity_type_five(char *map_info, size_t *i)
{
	check_three(map_info, i, "double");
	check_three(map_info, i, "double");
	check_doub(map_info, i);
	check_doub(map_info, i);
	check_three(map_info, i, "int");
}

