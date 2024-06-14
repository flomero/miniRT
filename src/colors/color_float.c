/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:34:21 by flfische          #+#    #+#             */
/*   Updated: 2024/06/14 15:09:25 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Converts a color from uint32_t to float values in the range [0, 1].
 *
 * @param color The color to convert.
 * @param fcolor The color to store the result in.
 */
void	ft_color_to_float(uint32_t color, t_color *fcolor)
{
	fcolor->r = (float)((color >> 24) & 0xFF) / 255.0;
	fcolor->g = (float)((color >> 16) & 0xFF) / 255.0;
	fcolor->b = (float)((color >> 8) & 0xFF) / 255.0;
}

/**
 * @brief Converts a color from float values in the range [0, 1] to uint32_t.
 *
 * @param fcolor The color to convert.
 * @return uint32_t The converted color.
 */
uint32_t	ft_color_from_float(t_color fcolor)
{
	uint32_t	color;

	color = 0;
	color |= (uint32_t)(fcolor.r * 255.0) << 24;
	color |= (uint32_t)(fcolor.g * 255.0) << 16;
	color |= (uint32_t)(fcolor.b * 255.0) << 8;
	color |= 0xFF;
	return (color);
}