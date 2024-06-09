/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:41:37 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/09 16:53:05 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*get_A(char **tokens)
{
	t_object	*obj;
	int			i;
	float		ratio;
	char		**rgb;

	if (get_arr_len(tokens) != 3)
		return (NULL);
	if (!is_float(tokens[1]) && !is_int(tokens[1]))
		return (NULL);
	ratio = (float) ft_atod(tokens[1]);
	if (ratio < 0 || ratio > 1)
		return (NULL);
	rgb = ft_split(tokens[2], ',');
	i = 0;
	while (rgb[i])
	{
		if (!is_int(rgb[i]) || ft_atoi(rgb[i]) > 255 || ft_atoi(rgb[i]) < 0)
			return (free_str_arr(rgb), NULL);
		i++;
	}
	if (get_arr_len(rgb) != 3)
		return (free_str_arr(rgb), NULL);
	obj = malloc (sizeof(t_object));
	if (!obj)
	{
		free_str_arr(rgb);
		return (ft_print_error("Allocation error"), NULL);
	}
	obj->s_ambient_light.ratio = ratio;
	obj->type = AMBIENT_LIGHT;
	obj->color = int_to_rgb(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	free_str_arr(rgb);
	return (obj);
}

t_object	*get_C(char **tokens)
{
	t_object	*obj;
	tokens = NULL;
	obj = NULL;
	return (obj);
}

t_object	*get_L(char **tokens)
{
	t_object	*obj;
	tokens = NULL;
	obj = NULL;
	return (obj);
}

t_object	*get_sp(char **tokens)
{
	t_object	*obj;
	tokens = NULL;
	obj = NULL;
	return (obj);
}

t_object	*get_pl(char **tokens)
{
	t_object	*obj;
	tokens = NULL;
	obj = NULL;
	return (obj);
}

t_object	*get_cy(char **tokens)
{
	t_object	*obj;
	tokens = NULL;
	obj = NULL;
	return (obj);
}

