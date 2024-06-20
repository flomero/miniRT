/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:39:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/20 18:14:17 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
Cone equation: x^2 + y^2 = (tan(angle))^2 * z^2
Ray equation: p = o + td
Substitute ray equation into cone equation and solve it.
A = d.x^2 + d.y^2 - (tan(angle))^2 * d.z^2
B = 2(o.x * d.x + o.y * d.y - (tan(angle))^2 * o.z * d.z)
C = o.x^2 + o.y^2 - (tan(angle))^2 * o.z^2
t = (-B +- sqrt(B^2 - 4AC)) / 2A
*/
float	ft_cone_hit(t_object *cone, t_ray *ray)
{
	return (INFINITY);
}

int	ft_cylinder_normal(t_hit *hit, t_ray *ray)
{
	return(1);
}
