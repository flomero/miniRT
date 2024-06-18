/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:21:56 by flfische          #+#    #+#             */
/*   Updated: 2024/06/13 10:28:22 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Calculates the length of a vector.
 *
 * @param a The vector.
 * @return The length of the vector.
 */
float	ft_v3_len(const t_vector3 *a)
{
	return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z));
}
