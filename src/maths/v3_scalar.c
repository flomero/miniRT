/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_scalar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:24:04 by flfische          #+#    #+#             */
/*   Updated: 2024/06/08 14:34:43 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Multiplies a vector by a scalar.
 *
 * @param a The vector.
 * @param scalar The scalar.
 * @return The new vector.
 * @note The function allocates memory.
 */
t_vector3	*ft_v3_scalar(t_vector3 *a, float scalar)
{
	t_vector3	*vector;

	vector = ft_v3_new(a->x * scalar, a->y * scalar, a->z * scalar);
	return (vector);
}

/**
 * Multiplies a vector by a scalar in place.
 *
 * @param a The vector.
 * @param scalar The scalar.
 * @return The vector with the scalar applied.
 */
t_vector3	*ft_v3_scalar_ip(t_vector3 *a, float scalar)
{
	a->x *= scalar;
	a->y *= scalar;
	a->z *= scalar;
	return (a);
}
