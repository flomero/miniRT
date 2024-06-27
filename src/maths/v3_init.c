/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:58:13 by flfische          #+#    #+#             */
/*   Updated: 2024/06/27 16:36:43 by klamprak         ###   ########.fr       */
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
t_vector3	*ft_v3_init(t_vector3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}
