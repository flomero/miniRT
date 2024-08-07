/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:16:11 by flfische          #+#    #+#             */
/*   Updated: 2024/07/04 15:26:06 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Subtracts two vectors: a - b.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The new vector.
 * @note The function allocates memory.
 */
// t_vector3	*ft_v3_sub(const t_vector3 *a, const t_vector3 *b)
// {
// 	t_vector3	*vector;

// 	vector = ft_v3_new(a->x - b->x, a->y - b->y, a->z - b->z);
// 	return (vector);
// }

/**
 * Subtracts two vectors and stores the result in the first vector: a -= b.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The first vector with the difference of the two vectors.
 */
t_vector3	*ft_v3_sub_ip(t_vector3 *a, const t_vector3 *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
	return (a);
}
