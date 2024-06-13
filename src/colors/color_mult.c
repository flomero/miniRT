/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:28:34 by flfische          #+#    #+#             */
/*   Updated: 2024/06/13 12:42:36 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdint.h>

int	ft_color_clamp(int color)
{
	if (color < 0)
		color = 0;
	if (color > 1)
		color = 1;
	return (color);
}

t_color	ft_color_float_mult(t_color color, float ratio)
{
	t_color	fcolor;

	fcolor.r = color.r * ratio;
	fcolor.g = color.g * ratio;
	fcolor.b = color.b * ratio;
	fcolor.r = ft_color_clamp(fcolor.r);
	fcolor.g = ft_color_clamp(fcolor.g);
	fcolor.b = ft_color_clamp(fcolor.b);
	return (fcolor);
}

t_color	ft_color_color_mult(t_color color1, t_color color2)
{
	t_color	fcolor;

	fcolor.r = color1.r * color2.r;
	fcolor.g = color1.g * color2.g;
	fcolor.b = color1.b * color2.b;
	fcolor.r = ft_color_clamp(fcolor.r);
	fcolor.g = ft_color_clamp(fcolor.g);
	fcolor.b = ft_color_clamp(fcolor.b);
	return (fcolor);
}
