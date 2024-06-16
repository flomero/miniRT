/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:49:43 by flfische          #+#    #+#             */
/*   Updated: 2024/06/16 17:18:33 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Loops through all pixels and sends a ray for each pixel.
 *
 * @param program The program.
 */
void	loop_pixels(t_program *program, int max_x, int max_y)
{
	int			x;
	int			y;
	uint32_t	color;
	int			pos;

	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			pos = x + y * WIN_WIDTH;
			color = ft_send_ray(x, y, ft_get_first_obj(CAMERA));
			if (program->current_sample == 0)
				program->colors_avgs[pos] = color;
			else
				program->colors_avgs[pos] = ft_new_avg_color(color,
						program->colors_avgs[pos], program->current_sample);
			mlx_put_pixel(program->image, x, y, program->colors_avgs[pos]);
			x++;
		}
		y++;
	}
}
