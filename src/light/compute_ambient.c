/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:21:29 by flfische          #+#    #+#             */
/*   Updated: 2024/06/16 17:42:30 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_init_ambient_base(t_color *result)
{
	t_object	*ambient_light;

	ambient_light = ft_get_first_obj(AMBIENT_LIGHT);
	*result = (t_color){0, 0, 0};
	ft_color_color_add(*result, ambient_light->color_f, result);
	ft_color_float_mult(*result, ambient_light->s_ambient_light.ratio, result);
}

/**
 * @brief Computes the ambient light of the scene.
 *
 * @param result The color to store the result in.
 * @param color The color to compute the ambient light for.
 * @return t_color* The computed color.
 */
t_color	*ft_compute_ambient(t_color *result, const t_color color)
{
	return (ft_color_color_mult(color, ft_get_program()->ambient_base, result));
}
