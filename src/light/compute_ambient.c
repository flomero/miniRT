/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:21:29 by flfische          #+#    #+#             */
/*   Updated: 2024/06/14 15:07:08 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Computes the ambient light of the scene.
 *
 * @param result The color to store the result in.
 * @param color The color to compute the ambient light for.
 * @return t_color* The computed color.
 */
t_color	*ft_compute_ambient(t_color *result, const t_color color)
{
	static t_object	*ambient_light = NULL;
	static t_color	ambient_color;

	if (ambient_light)
		return (ft_color_color_mult(color, ambient_color, result));
	ambient_light = ft_get_first_obj(AMBIENT_LIGHT);
	ambient_color = (t_color){0, 0, 0};
	ft_color_color_add(ambient_color, ambient_light->color_f, &ambient_color);
	ft_color_float_mult(ambient_color, ambient_light->s_ambient_light.ratio,
		&ambient_color);
	return (ft_color_color_mult(color, ambient_color, result));
}
