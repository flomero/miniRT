/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:39:59 by flfische          #+#    #+#             */
/*   Updated: 2024/06/09 15:24:05 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector3	*ft_v3_copy(t_vector3 *v)
{
	t_vector3	*result;

	result = (t_vector3 *)malloc(sizeof(t_vector3));
	if (!result)
		return (NULL);
	result->x = v->x;
	result->y = v->y;
	result->z = v->z;
	return (result);
}
