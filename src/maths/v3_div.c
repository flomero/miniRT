/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_div.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:34:07 by flfische          #+#    #+#             */
/*   Updated: 2024/07/04 15:15:50 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Divides a vector by a scalar.
 *
 * @param v The vector to divide.
 * @param t The scalar to divide by.
 * @return The divided vector.
 * @note The returned vector must be freed.
 */
// t_vector3	*ft_v3_div(const t_vector3 *v, double t)
// {
// 	t_vector3	*result;

// 	result = (t_vector3 *)malloc(sizeof(t_vector3));
// 	if (!result)
// 		return (NULL);
// 	result->x = v->x / t;
// 	result->y = v->y / t;
// 	result->z = v->z / t;
// 	return (result);
// }

/**
 * Divides a vector by a scalar.
 *
 * @param v The vector to divide.
 * @param t The scalar to divide by.
 * @return The divided vector.
 */
t_vector3	*ft_v3_div_ip(t_vector3 *v, double t)
{
	v->x /= t;
	v->y /= t;
	v->z /= t;
	return (v);
}
