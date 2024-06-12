/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:21:29 by flfische          #+#    #+#             */
/*   Updated: 2024/06/12 11:41:04 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	ft_compute_ambient(uint32_t color)
{
	static t_object	*ambient_light = NULL;
	static uint32_t	ambient_color = 0;

	if (ambient_light)
		return (ft_color_color_mult(color, ambient_color));
	ambient_light = ft_get_first_obj(AMBIENT_LIGHT);
	ambient_color = ambient_light->color;
	ambient_color = ft_color_float_mult(ambient_color,
			ambient_light->s_ambient_light.ratio);
	return (ft_color_color_mult(color, ambient_color));
}
