/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:13:49 by flfische          #+#    #+#             */
/*   Updated: 2024/07/04 15:16:12 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Adds two vectors and returns the result.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The sum of the two vectors.
 * @note The function allocates memory.
 */
// t_vector3	*ft_v3_add(const t_vector3 *a, const t_vector3 *b)
// {
// 	t_vector3	*vector;

// 	vector = ft_v3_new(a->x + b->x, a->y + b->y, a->z + b->z);
// 	return (vector);
// }

/**
 * Adds two vectors and stores the result in the first vector.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The first vector with the sum of the two vectors.
 */
t_vector3	*ft_v3_add_ip(t_vector3 *a, const t_vector3 *b)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
	return (a);
}
