/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:21:29 by flfische          #+#    #+#             */
/*   Updated: 2024/06/13 12:45:25 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	ft_compute_ambient(const t_color color)
{
	static t_object	*ambient_light = NULL;
	static t_color	ambient_color;

	if (ambient_light)
		return (ft_color_color_mult(color, ambient_color));
	ambient_light = ft_get_first_obj(AMBIENT_LIGHT);
	ambient_color = ambient_light->color_f;
	ambient_color = ft_color_float_mult(ambient_color,
			ambient_light->s_ambient_light.ratio);
	return (ft_color_color_mult(color, ambient_color));
}
