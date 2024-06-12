/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:55:21 by flfische          #+#    #+#             */
/*   Updated: 2024/06/12 11:58:09 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	ft_color_color_add(uint32_t color1, uint32_t color2)
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;

	red = ((color1 & 0xFF0000) >> 16) + ((color2 & 0xFF0000) >> 16);
	green = ((color1 & 0xFF00) >> 8) + ((color2 & 0xFF00) >> 8);
	blue = (color1 & 0xFF) + (color2 & 0xFF);
	if (red > 0xFF)
		red = 0xFF;
	if (green > 0xFF)
		green = 0xFF;
	if (blue > 0xFF)
		blue = 0xFF;
	return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}
