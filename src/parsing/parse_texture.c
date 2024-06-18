/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:48:00 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 18:58:31 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	get_tex_file(char **tokens, t_object *obj)
{
	int	fd;

	obj->type = TEXTURE;
	obj->s_tex.type = TEX_FILE;
	if (get_arr_len(tokens) != 3)
		return (FALSE);
	obj->s_tex.name = ft_strdup(tokens[1]);
	obj->s_tex.s_custom.path = ft_strdup(tokens[2]);
	fd = open(obj->s_tex.s_custom.path, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close(fd);
	return (TRUE);
}

t_bool	get_tex_checker(char **tokens, t_object *obj, t_bool UV)
{
	obj->type = TEXTURE;
	if (UV)
		obj->s_tex.type = TEX_UVCHECKER;
	else
		obj->s_tex.type = TEX_CHECKER;
	if (get_arr_len(tokens) != 5)
		return (FALSE);
	obj->s_tex.name = ft_strdup(tokens[1]);
	if (!get_color(tokens[2], &obj->s_tex.s_checker.color1))
		return (FALSE);
	if (!get_color(tokens[3], &obj->s_tex.s_checker.color2))
		return (FALSE);
	if (!is_int(tokens[4]) && !is_float(tokens[4]))
		return (FALSE);
	obj->s_tex.s_checker.size = (float)ft_atod(tokens[4]);
	return (TRUE);
}
