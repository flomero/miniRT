/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:41:37 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/10 13:51:04 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*get_A(char **tokens)
{
	t_object	*obj;
	float		ratio;

	obj = malloc (sizeof(t_object *));
	if (!obj)
		return (ft_print_error("Allocation error"), NULL);
	if (get_arr_len(tokens) != 3)
		return (free(obj), NULL);
	if (!is_float(tokens[1]) && !is_int(tokens[1]))
		return (free(obj), NULL);
	ratio = (float) ft_atod(tokens[1]);
	if (ratio < 0 || ratio > 1)
		return (free(obj), NULL);
	if (!get_color(tokens[2], &obj->color))
		return (free(obj), NULL);
	obj->s_ambient_light.ratio = ratio;
	obj->type = AMBIENT_LIGHT;
	return (obj);
}

t_object	*get_C(char **tokens)
{
	t_object	*obj;
	float		fov;

	obj = malloc (sizeof(t_object *));
	if (!obj)
		return (ft_print_error("Allocation error"), NULL);
	obj->type = CAMERA;
	obj->color = 0;
	if (get_arr_len(tokens) != 4)
		return (free(obj), NULL);
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(obj), NULL);
	if (!get_vector(&obj->s_camera.normal, tokens[2]))
		return (free(obj), NULL);
	if (!in_range(&obj->s_camera.normal, -1, 1))
		return (free(obj), NULL);
	if (!is_float(tokens[3]) && !is_int(tokens[3]))
		return (free(obj), NULL);
	fov = (float) ft_atod(tokens[3]);
	if (fov < 0 || fov > 180)
		return (free(obj), NULL);
	obj->s_camera.fov = fov;
	return (obj);
}

t_object	*get_L(char **tokens)
{
	t_object	*obj;
	float		brightness;

	obj = malloc (sizeof(t_object *));
	if (!obj)
		return (ft_print_error("Allocation error"), NULL);
	obj->type = LIGHT;
	if (get_arr_len(tokens) != 4)
		return (free(obj), NULL);
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(obj), NULL);
	if (!is_float(tokens[2]) && !is_int(tokens[2]))
		return (free(obj), NULL);
	brightness = (float) ft_atod(tokens[2]);
	if (brightness < 0 || brightness > 1)
		return (free(obj), NULL);
	if (!get_color(tokens[3], &obj->color))
		return (free(obj), NULL);
	obj->s_light.brightness = brightness;
	return (obj);
}

t_object	*get_sp(char **tokens)
{
	t_object	*obj;
	float		diameter;

	obj = malloc (sizeof(t_object *));
	if (!obj)
		return (ft_print_error("Allocation error"), NULL);
	obj->type = SPHERE;
	if (get_arr_len(tokens) != 4)
		return (free(obj), NULL);
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(obj), NULL);
	if (!is_float(tokens[2]) && !is_int(tokens[2]))
		return (free(obj), NULL);
	diameter = (float) ft_atod(tokens[2]);
	if (!get_color(tokens[3], &obj->color))
		return (free(obj), NULL);
	obj->s_sphere.diameter = diameter;
	return (obj);
}

t_object	*get_pl(char **tokens)
{
	t_object	*obj;

	obj = malloc (sizeof(t_object *));
	if (!obj)
		return (ft_print_error("Allocation error"), NULL);
	obj->type = PLANE;
	if (get_arr_len(tokens) != 4)
		return (free(obj), NULL);
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(&obj), NULL);
	if (!get_vector(&obj->s_plane.normal, tokens[2]))
		return (free(obj), NULL);
	if (!in_range(&obj->s_plane.normal, -1, 1))
		return (free(obj), NULL);
	if (!get_color(tokens[3], &obj->color))
		return (free(obj), NULL);
	return (obj);
}

t_object	*get_cy(char **tokens)
{
	t_object	*obj;
	float		diameter;
	float		height;

	obj = malloc (sizeof(t_object *));
	if (!obj)
		return (ft_print_error("Allocation error"), NULL);
	obj->type = CYLINDER;
	if (get_arr_len(tokens) != 6)
		return (free(obj), NULL);
	obj->pos.x = 10;
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(obj), NULL);
	exit(1);
	if (!get_vector(&obj->s_cylinder.normal, tokens[2]))
		return (free(obj), NULL);
	if (!in_range(&obj->s_cylinder.normal, -1, 1))
		return (free(obj), NULL);
	if (!is_float(tokens[3]) && !is_int(tokens[3]))
		return (free(obj), NULL);
	diameter = (float) ft_atod(tokens[3]);
	if (!is_float(tokens[4]) && !is_int(tokens[4]))
		return (free(obj), NULL);
	height = (float) ft_atod(tokens[4]);
	if (!get_color(tokens[5], &obj->color))
		return (free(obj), NULL);
	obj->s_cylinder.diameter = diameter;
	obj->s_cylinder.height = height;
	return (obj);
}

