/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:16:11 by flfische          #+#    #+#             */
/*   Updated: 2024/06/08 14:16:31 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector3	*ft_v3_sub(t_vector3 *a, t_vector3 *b)
{
	t_vector3	*vector;

	vector = ft_v3_new(a->x - b->x, a->y - b->y, a->z - b->z);
	return (vector);
}
