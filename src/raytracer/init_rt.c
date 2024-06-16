/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:25:16 by flfische          #+#    #+#             */
/*   Updated: 2024/06/16 17:40:36 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint32_t	init_void_color(void)
{
	t_object	*ambient_light;
	t_color		color;

	ambient_light = ft_get_first_obj(AMBIENT_LIGHT);
	color = (t_color){0, 0, 0};
	ft_color_color_add(color, ambient_light->color_f, &color);
	ft_color_float_mult(color, ambient_light->s_ambient_light.ratio, &color);
	ft_color_float_mult(color, BACKGROUND_FACTOR, &color);
	return (ft_color_from_float(color));
}

/**
 * Initializes the raytracer.
 *
 * @param program The program.
 */
void	ft_init_rt(t_program *program)
{
	ft_calculate_viewport(ft_get_first_obj(CAMERA));
	program->void_color = init_void_color();
	ft_init_ambient_base(&program->ambient_base);
}
