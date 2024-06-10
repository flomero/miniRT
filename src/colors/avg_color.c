/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avg_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:35:03 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 11:56:15 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Calculates the average color of x colors.
 *
 * @param colors The colors to average.
 * @param x The number of colors to average.
 * @return The average color.
 */
uint32_t	ft_avg_color(uint32_t *colors, size_t x)
{
	uint32_t	avg;
	size_t		count;
	int			color[3];

	count = x;
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	while (x--)
	{
		color[0] += (colors[x] >> 24) & 0xFF;
		color[1] += (colors[x] >> 16) & 0xFF;
		color[2] += (colors[x] >> 8) & 0xFF;
	}
	color[0] /= count;
	color[1] /= count;
	color[2] /= count;
	avg = (color[0] << 24) | (color[1] << 16) | (color[2] << 8) | 0xFF;
	return (avg);
}
