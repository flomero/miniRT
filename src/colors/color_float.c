/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:34:21 by flfische          #+#    #+#             */
/*   Updated: 2024/06/13 12:45:14 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_color_to_float(uint32_t color, t_color *fcolor)
{
	fcolor->r = (float)((color & 0xFF0000) >> 16) / 255.0;
	fcolor->g = (float)((color & 0xFF00) >> 8) / 255.0;
	fcolor->b = (float)(color & 0xFF) / 255.0;
}

uint32_t	ft_color_from_float(t_color fcolor)
{
	uint32_t	color;

	color = (uint32_t)(fcolor.r * 255.0) << 16;
	color |= (uint32_t)(fcolor.g * 255.0) << 8;
	color |= (uint32_t)(fcolor.b * 255.0);
	return (color);
}
