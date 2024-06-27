/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_dotprod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:17:20 by flfische          #+#    #+#             */
/*   Updated: 2024/06/27 16:36:43 by klamprak         ###   ########.fr       */
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
double	ft_v3_dotprod(const t_vector3 *a, const t_vector3 *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
