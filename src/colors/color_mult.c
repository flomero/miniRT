/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:28:34 by flfische          #+#    #+#             */
/*   Updated: 2024/06/14 12:20:27 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdint.h>

float	ft_color_clamp(float color)
{
	if (color < 0)
		color = 0;
	if (color > 1)
		color = 1;
	return (color);
}

t_color	*ft_color_float_mult(t_color color, float ratio, t_color *result)
{
	static int x;

	if (x < 10)
	{
		printf("color: %08x\n", ft_color_from_float(color));
		printf("ratio: %f\n", ratio);
	}

	result->r = color.r * ratio;
	result->g = color.g * ratio;
	result->b = color.b * ratio;
	result->r = ft_color_clamp(result->r);
	result->g = ft_color_clamp(result->g);
	result->b = ft_color_clamp(result->b);

	if (x < 10)
	{
		printf("result: %08x\n", ft_color_from_float(*result));
		x++;
	}
	return (result);
}


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
