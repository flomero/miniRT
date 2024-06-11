/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:56:51 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 15:04:20 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Renders the next sample.
 *
 * @param param The program.
 */
void	ft_render(void *param)
{
	t_program	*program;

	program = (t_program *)param;
	if (program->current_sample < SAMPLES)
	{
		ft_printf("Rendering sample %d/%d\n", program->current_sample + 1,
			SAMPLES);
		loop_pixels(program);
		program->current_sample++;
	}
}

// TODO: free stuff on exit
/**
 * Handles key presses.
 *
 * @param keydata The key data.
 * @param param The program.
 */
void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_program	*program;

	program = (t_program *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_terminate(program->mlx);
		exit(0);
	}
	if (keydata.key == MLX_KEY_SPACE)
		program->current_sample = 0;
}
