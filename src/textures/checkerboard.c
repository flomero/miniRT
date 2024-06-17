/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:04:06 by flfische          #+#    #+#             */
/*   Updated: 2024/06/17 19:12:54 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	ft_checkerboard(t_material *material, const t_vector3 *point,
		t_color *result)
{
	float	px;
	float	pz;

	px = floor(point->x / material->s_checker.size);
	pz = floor(point->z / material->s_checker.size);
	if ((int)(px + pz) % 2 == 0)
	{
		ft_color_to_float(material->s_checker.color1, result);
		return (material->s_checker.color1);
	}
	ft_color_to_float(material->s_checker.color2, result);
	return (material->s_checker.color2);
}
