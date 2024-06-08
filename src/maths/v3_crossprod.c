/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_crossprod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:18:51 by flfische          #+#    #+#             */
/*   Updated: 2024/06/08 14:19:27 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector3	*ft_v3_crossprod(t_vector3 *a, t_vector3 *b)
{
	t_vector3	*vector;

	vector = ft_v3_new(a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z,
			a->x * b->y - a->y * b->x);
	return (vector);
}
