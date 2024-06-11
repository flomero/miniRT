/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:58:13 by flfische          #+#    #+#             */
/*   Updated: 2024/06/11 09:59:59 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Initializes a 3D vector.
 *
 * @param v The 3D vector.
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @param z The z coordinate.
 * @return The 3D vector.
 */
t_vector3	*ft_v3_init(t_vector3 *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}
