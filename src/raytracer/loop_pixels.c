/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:49:43 by flfische          #+#    #+#             */
/*   Updated: 2024/06/17 14:59:18 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Loops through all pixels and sends a ray for each pixel.
 *
 * @param program The program.
 */
void	loop_pixels(t_program *program, int min_x, t_vector2 *max, int sample)
{
	int			x;
	int			y;
	uint32_t	color;
	int			pos;

	y = 0;
	if (min_x < 0)
		min_x = 0;
	while (y < max->y && y < WIN_HEIGHT)
	{
		x = min_x;
		while (x < max->x && x < WIN_WIDTH)
		{
			pos = x + y * WIN_WIDTH;
			color = ft_send_ray(x, y, ft_get_first_obj(CAMERA));
			if (sample == 0)
				program->colors_avgs[pos] = color;
			else
				program->colors_avgs[pos] = ft_new_avg_color(color,
						program->colors_avgs[pos], sample);
			mlx_put_pixel(program->image, x, y, program->colors_avgs[pos]);
			x++;
		}
		y++;
	}
}
