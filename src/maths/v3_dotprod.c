/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_dotprod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:17:20 by flfische          #+#    #+#             */
/*   Updated: 2024/06/08 14:34:07 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Calculates the dot product of two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product of the two vectors.
 */
float	ft_v3_dotprod(t_vector3 *a, t_vector3 *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
