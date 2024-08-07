/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:28:34 by flfische          #+#    #+#             */
/*   Updated: 2024/06/27 16:36:43 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdint.h>

double	ft_color_clamp(double color)
{
	if (color < 0)
		color = 0;
	if (color > 1)
		color = 1;
	return (color);
}

/**
 * @brief Multiplies a color by a double value.
 * @param color The color to multiply.
 * @param ratio The double value to multiply the color by.
 * @param result The color to store the result in.
 * @return t_color* The multiplied color.
 */
t_color	*ft_color_float_mult(t_color color, double ratio, t_color *result)
{
	result->r = color.r * ratio;
	result->g = color.g * ratio;
	result->b = color.b * ratio;
	result->r = ft_color_clamp(result->r);
	result->g = ft_color_clamp(result->g);
	result->b = ft_color_clamp(result->b);
	return (result);
}

/**
 * @brief Multiplies two colors together.
 * @param color1 The first color.
 * @param color2 The second color.
 * @param result The color to store the result in.
 * @return t_color* The multiplied color.
 */
t_color	*ft_color_color_mult(t_color color1, t_color color2, t_color *result)
{
	result->r = color1.r * color2.r;
	result->g = color1.g * color2.g;
	result->b = color1.b * color2.b;
	result->r = ft_color_clamp(result->r);
	result->g = ft_color_clamp(result->g);
	result->b = ft_color_clamp(result->b);
	return (result);
}
