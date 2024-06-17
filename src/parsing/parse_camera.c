/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:03:03 by flfische          #+#    #+#             */
/*   Updated: 2024/06/17 16:07:36 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_c_config(char **tokens, int len)
{
	t_program	*program;

	program = ft_get_program();
	if (len == 5 && !ft_atoi(tokens[4]))
		return (0);
	if (len >= 5)
		program->max_samples = ft_atoi(tokens[4]);
	if (len == 6 && !ft_atoi(tokens[5]))
		return (0);
	if (len >= 6)
		program->bounces = ft_atoi(tokens[5]);
	if (len == 7 && !ft_atoi(tokens[6]))
		return (0);
	if (len == 7)
		program->thread_count = ft_atoi(tokens[6]);
	return (1);
}

/**
 * @brief Get the c object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_c(char **tokens, t_object *obj)
{
	float	fov;

	obj->type = CAMERA;
	obj->color = 0;
	if (get_arr_len(tokens) < 4 || get_arr_len(tokens) > 7)
		return (0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (0);
	if (!get_vector(&obj->s_camera.normal, tokens[2]))
		return (0);
	if (!in_range(&obj->s_camera.normal, -1, 1))
		return (0);
	if (!is_float(tokens[3]) && !is_int(tokens[3]))
		return (0);
	fov = (float)ft_atod(tokens[3]);
	if (fov < 0 || fov > 180)
		return (0);
	if (!get_c_config(tokens, get_arr_len(tokens)))
		return (0);
	obj->s_camera.fov = fov;
	return (1);
}
