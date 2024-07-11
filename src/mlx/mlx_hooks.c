/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:56:51 by flfische          #+#    #+#             */
/*   Updated: 2024/07/11 12:51:05 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief exit program when user clicks on the close button
 *
 * @param param
 */
void	ft_program_exit(void *param)
{
	t_program	*program;

	program = (t_program *)param;
	if (program->thread_count > 1)
	{
		pthread_mutex_lock(program->stop);
		program->stop_threads = TRUE;
		pthread_mutex_unlock(program->stop);
		join_threads(program);
	}
	mlx_delete_image(program->mlx, program->image);
	mlx_terminate(program->mlx);
	ft_free_all();
	exit(0);
}

/**
 * Renders the next sample.
 *
 * @param param The program.
 */
void	ft_render(void *param)
{
	t_program	*program;
	t_vector2	max;

	program = (t_program *)param;
	max = (t_vector2){WIN_WIDTH, WIN_HEIGHT};
	if (program->current_sample < program->max_samples)
	{
		ft_printf("\033[2K\rRendering sample %d/%d", program->current_sample
			+ 1, program->max_samples);
		loop_pixels(program, 0, &max, program->current_sample);
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
	t_vector2	max;
	int			thread_id;

	thread_id = (int)(uintptr_t)param;
	program = ft_get_program();
	if (thread_id == program->thread_count - 1)
		max.x = WIN_WIDTH;
	else
		max.x = (WIN_WIDTH / program->thread_count) * (thread_id + 1);
	max.y = WIN_HEIGHT;
	while (program->thread_samples[thread_id] < program->max_samples)
	{
		pthread_mutex_lock(program->stop);
		if (program->stop_threads)
			return (pthread_mutex_unlock(program->stop), NULL);
		pthread_mutex_unlock(program->stop);
		if (thread_id == 0)
			ft_printf("\033[2K\rRendering sample %d/%d",
				program->thread_samples[thread_id] + 1, program->max_samples);
		loop_pixels(program, (WIN_WIDTH / program->thread_count) * thread_id,
			&max, program->thread_samples[thread_id]);
		program->thread_samples[thread_id]++;
	}
	return (NULL);
}

void	ft_render_multithread(void *param)
{
	t_program		*program;
	int				i;
	static t_bool	initialized;

	if (initialized)
		return ;
	initialized = TRUE;
	program = (t_program *)param;
	i = 0;
	ft_debug_message("Rendering multithread...");
	while (i < program->thread_count && i < MAX_THREADS)
	{
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
		if (program->thread_count > 1)
		{
			pthread_mutex_lock(program->stop);
			program->stop_threads = TRUE;
			pthread_mutex_unlock(program->stop);
			join_threads(program);
		}
		mlx_delete_image(program->mlx, program->image);
		mlx_terminate(program->mlx);
		ft_free_all();
		exit(0);
	}
	if (keydata.key == MLX_KEY_SPACE)
		program->current_sample = 0;
}
