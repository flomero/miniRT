/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:49:43 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 14:00:53 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Loops through all pixels and sends a ray for each pixel.
 *
 * @param program The program.
 */
void	loop_pixels(t_program *program)
{
	int			x;
	int			y;
	uint32_t	color;
	uint32_t	avg_color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			color = ft_send_ray(x, y, &program->objects[0]);
			if (program->current_sample == 0)
				program->colors_avgs[x][y] = color;
			else
			{
				avg_color = program->colors_avgs[x][y];
				program->colors_avgs[x][y] = ft_new_avg_color(color, avg_color,
						program->current_sample);
			}
			mlx_put_pixel(program->image, x, y, program->colors_avgs[x][y]);
			x++;
		}
		y++;
	}
}
