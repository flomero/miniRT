/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:25:16 by flfische          #+#    #+#             */
/*   Updated: 2024/07/06 19:08:59 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint32_t	init_void_color(void)
{
	t_object	*ambient_light;
	t_color		color;

	ambient_light = ft_get_first_obj(AMBIENT_LIGHT);
	color = (t_color){0, 0, 0};
	ft_color_color_add(color, ambient_light->color_f, &color);
	ft_color_float_mult(color, ambient_light->s_ambient_light.ratio, &color);
	ft_color_float_mult(color, BACKGROUND_FACTOR, &color);
	return (ft_color_from_float(color));
}

static void	print_stats(t_program *program)
{
	ft_printf("Rendering with %d", program->max_samples);
	if (program->max_samples == 1)
		ft_printf(" sample");
	else
		ft_printf(" samples");
	ft_printf(" and %d", program->thread_count);
	if (program->thread_count == 1)
		ft_printf(" thread");
	else
		ft_printf(" threads");
	ft_printf(" and %d", program->bounces);
	if (program->bounces == 1)
		ft_printf(" bounce\n");
	else
		ft_printf(" bounces\n");
}

/**
 * Initializes the raytracer.
 *
 * @param program The program.
 */
t_bool	ft_init_rt(t_program *program)
{
	ft_calculate_viewport(ft_get_first_obj(CAMERA));
	program->void_color = init_void_color();
	ft_init_ambient_base(&program->ambient_base);
	program->stop_threads = FALSE;
	program->current_sample = 0;
	if (!program->max_samples)
		program->max_samples = DEFAULT_SAMPLES;
	if (!program->thread_count)
		program->thread_count = DEFAULT_THREADS;
	if (program->thread_count > MAX_THREADS)
		program->thread_count = MAX_THREADS;
	if (!program->bounces)
		program->bounces = DEFAULT_BOUNCES;
	if (program->thread_count > 1)
	{
		program->stop = malloc(sizeof(pthread_mutex_t));
		if (!program->stop)
			return (ft_print_error(strerror(errno)), FALSE);
		if (pthread_mutex_init(program->stop, NULL))
			return (ft_print_error(strerror(errno)), FALSE);
	}
	print_stats(program);
	return (TRUE);
}
