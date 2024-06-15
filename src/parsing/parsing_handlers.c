/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:41:37 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/15 12:05:50 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Get the a object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_a(char **tokens, t_object *obj)
{
	float	ratio;

	if (get_arr_len(tokens) != 3)
		return (free(obj), 0);
	if (!is_float(tokens[1]) && !is_int(tokens[1]))
		return (free(obj), 0);
	ratio = (float)ft_atod(tokens[1]);
	if (ratio < 0 || ratio > 1)
		return (free(obj), 0);
	if (!get_color(tokens[2], &obj->color))
		return (free(obj), 0);
	ft_color_to_float(obj->color, &obj->color_f);
	obj->s_ambient_light.ratio = ratio;
	obj->type = AMBIENT_LIGHT;
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
	if (get_arr_len(tokens) != 4)
		return (free(obj), 0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(obj), 0);
	if (!get_vector(&obj->s_camera.normal, tokens[2]))
		return (free(obj), 0);
	if (!in_range(&obj->s_camera.normal, -1, 1))
		return (free(obj), 0);
	if (!is_float(tokens[3]) && !is_int(tokens[3]))
		return (free(obj), 0);
	fov = (float)ft_atod(tokens[3]);
	if (fov < 0 || fov > 180)
		return (free(obj), 0);
	obj->s_camera.fov = fov;
	return (1);
}

/**
 * @brief Get the l object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_l(char **tokens, t_object *obj)
{
	float	brightness;

	obj->type = LIGHT;
	if (get_arr_len(tokens) != 4)
		return (free(obj), 0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(obj), 0);
	if (!is_float(tokens[2]) && !is_int(tokens[2]))
		return (free(obj), 0);
	brightness = (float)ft_atod(tokens[2]);
	if (brightness < 0 || brightness > 1)
		return (free(obj), 0);
	if (!get_color(tokens[3], &obj->color))
		return (free(obj), 0);
	ft_color_to_float(obj->color, &obj->color_f);
	obj->s_light.brightness = brightness;
	return (1);
}

/**
 * @brief Get the sp object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_sp(char **tokens, t_object *obj)
{
	float	diameter;

	obj->type = SPHERE;
	if (get_arr_len(tokens) < 4 || get_arr_len(tokens) > 5)
		return (free(obj), 0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(obj), 0);
	if (!is_float(tokens[2]) && !is_int(tokens[2]))
		return (free(obj), 0);
	diameter = (float)ft_atod(tokens[2]);
	if (!get_color(tokens[3], &obj->color))
		return (free(obj), 0);
	ft_color_to_float(obj->color, &obj->color_f);
	obj->s_sphere.diameter = diameter;
	obj->material.specular = DEFAULT_SPECULAR;
	obj->material.shininess = DEFAULT_SHININESS;
	obj->material.diffuse = DEFAULT_DIFFUSE;
	obj->material.reflectivness = DEFAULT_REFLECTIVNESS;
	if (tokens[4] && (!is_float(tokens[4]) && !is_int(tokens[4])))
		return (0);
	if (tokens[4])
		obj->material.reflectivness = ft_atod(tokens[4]);
	if (obj->material.reflectivness > 0)
	{
		obj->material.diffuse = (1 - obj->material.reflectivness)
			* DEFAULT_DIFFUSE;
		obj->material.specular = obj->material.reflectivness * DEFAULT_SPECULAR;
	}
	return (1);
}

/**
 * @brief Get the pl object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_pl(char **tokens, t_object *obj)
{
	obj->type = PLANE;
	if (get_arr_len(tokens) != 4)
		return (free(obj), 0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(&obj), 0);
	if (!get_vector(&obj->s_plane.normal, tokens[2]))
		return (free(obj), 0);
	if (!in_range(&obj->s_plane.normal, -1, 1))
		return (free(obj), 0);
	if (!get_color(tokens[3], &obj->color))
		return (free(obj), 0);
	return (1);
}

/*
int	get_cy(char **tokens, t_object	*obj): This implementation is on
parsing_utils3.c in order for norminette to aprove it.
 */
