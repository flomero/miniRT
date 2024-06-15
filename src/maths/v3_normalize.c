/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_normalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:20:48 by flfische          #+#    #+#             */
/*   Updated: 2024/06/15 14:09:05 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Normalizes a vector.
 *
 * @param a The vector.
 * @return The normalized vector.
 * @note The function allocates memory.
 */
t_vector3	*ft_v3_normal(const t_vector3 *a)
{
	float		len;
	t_vector3	*vector;

	len = ft_v3_len(a);
	vector = ft_v3_new(a->x / len, a->y / len, a->z / len);
	return (vector);
}

/**
 * Normalizes a vector in place.
 *
 * @param a The vector.
 * @return The normalized vector.
 */
t_vector3	*ft_v3_normal_ip(t_vector3 *a)
{
	float	len;

	len = ft_v3_len(a);
	if (len == 0)
		return (a);
	a->x /= len;
	a->y /= len;
	a->z /= len;
	return (a);
}
