/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:28:34 by flfische          #+#    #+#             */
/*   Updated: 2024/06/12 11:39:45 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	ft_color_float_mult(uint32_t color, float ratio)
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;

	red = (color & 0xFF0000) >> 16;
	green = (color & 0xFF00) >> 8;
	blue = color & 0xFF;
	red = (uint32_t)(red * ratio);
	green = (uint32_t)(green * ratio);
	blue = (uint32_t)(blue * ratio);
	return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}

uint32_t	ft_color_color_mult(uint32_t color1, uint32_t color2)
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;

	red = ((color1 & 0xFF0000) >> 16) * ((color2 & 0xFF0000) >> 16);
	green = ((color1 & 0xFF00) >> 8) * ((color2 & 0xFF00) >> 8);
	blue = (color1 & 0xFF) * (color2 & 0xFF);
	return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}
