/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_crossprod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:18:51 by flfische          #+#    #+#             */
/*   Updated: 2024/06/08 14:33:23 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Calculates the cross product of two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The cross product of the two vectors. NULL if the allocation fails.
 * @note The function allocates memory.
 */
t_vector3	*ft_v3_crossprod(t_vector3 *a, t_vector3 *b)
{
	t_vector3	*vector;

	vector = ft_v3_new(a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z,
			a->x * b->y - a->y * b->x);
	return (vector);
}

/**
 * Calculates the cross product of two vectors and stores the result in the
 * first vector.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The first vector with the cross product of the two vectors.
 */
t_vector3	*ft_v3_crossprod_ip(t_vector3 *a, t_vector3 *b)
{
	float	x;
	float	y;
	float	z;

	x = a->y * b->z - a->z * b->y;
	y = a->z * b->x - a->x * b->z;
	z = a->x * b->y - a->y * b->x;
	a->x = x;
	a->y = y;
	a->z = z;
	return (a);
}
