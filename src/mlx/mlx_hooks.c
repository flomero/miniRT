/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:56:51 by flfische          #+#    #+#             */
/*   Updated: 2024/06/17 13:00:33 by flfische         ###   ########.fr       */
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
		ft_printf("\033[2K\rRendering sample %d/%d", program->current_sample
			+ 1, SAMPLES);
		loop_pixels(program, 0, WIN_WIDTH, WIN_HEIGHT);
		program->current_sample++;
	}
}

/**
 * Renders the next sample.
 *
 * @param thread_id The thread id.
 */
void	*ft_render_multi(void *param)
{
	t_program	*program;
	int			x_start;
	int			x_end;
	int			height;
	int			thread_id;

	thread_id = (int)(uintptr_t)param;
	program = ft_get_program();
	if (thread_id == program->thread_count - 1)
		x_end = WIN_WIDTH;
	else
		x_end = (WIN_WIDTH / program->thread_count) * (thread_id + 1);
	x_start = (WIN_WIDTH / program->thread_count) * thread_id;
	height = WIN_HEIGHT;
	program->thread_samples[thread_id] = 0;
	while (program->thread_samples[thread_id] < SAMPLES)
	{
		if (thread_id == 0)
			ft_printf("\033[2K\rRendering sample %d/%d",
				program->thread_samples[thread_id] + 1, SAMPLES);
		loop_pixels(program, x_start, x_end, height);
		program->thread_samples[thread_id]++;
	}
	return (NULL);
}

void	ft_render_multithread(void *param)
{
	t_program		*program;
	int				i;
	int				ids[MAX_THREADS];
	static t_bool	initialized;

	if (initialized)
		return ;
	initialized = TRUE;
	program = (t_program *)param;
	i = 0;
	while (i < program->thread_count && i < MAX_THREADS)
	{
		ids[i] = i;
		pthread_create(&program->threads[i], NULL, ft_render_multi,
			(void *)(uintptr_t)i);
		if (!program->threads[i])
			ft_print_error(strerror(errno));
		i++;
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
		join_threads(program);
		mlx_terminate(program->mlx);
		exit(0);
	}
	if (keydata.key == MLX_KEY_SPACE)
		program->current_sample = 0;
}
