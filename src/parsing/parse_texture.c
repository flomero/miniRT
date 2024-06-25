/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 18:48:00 by flfische          #+#    #+#             */
/*   Updated: 2024/06/25 17:01:13 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief parsing for the texture file
 * @param tokens the tokens to parse
 * @param obj the object to assign the parsed values
 * @note not yet used
 */
t_bool	get_tex_file(char **tokens, t_object *obj)
{
	int	fd;

	obj->type = TEXTURE;
	obj->s_tex.type = TEX_FILE;
	if (get_arr_len(tokens) != 3)
		return (FALSE);
	ft_bzero(obj->s_tex.name, MAX_NAME_LEN);
	ft_strlcpy(obj->s_tex.name, tokens[1], MAX_NAME_LEN);
	ft_bzero(obj->s_tex.s_custom.path, MAX_PATH_LEN);
	ft_strlcpy(obj->s_tex.s_custom.path, tokens[2], MAX_PATH_LEN);
	fd = open(obj->s_tex.s_custom.path, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	close(fd);
	obj->s_tex.s_custom.img = mlx_load_png(obj->s_tex.s_custom.path);
	if (obj->s_tex.s_custom.img == NULL)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief parsing for the texture checker
 * @param tokens the tokens to parse
 * @param obj the object to assign the parsed values
 * @param UV if the texture is UV or not
 */
t_bool	get_tex_checker(char **tokens, t_object *obj, t_bool UV)
{
	obj->type = TEXTURE;
	if (UV)
		obj->s_tex.type = TEX_UVCHECKER;
	else
		obj->s_tex.type = TEX_CHECKER;
	if (get_arr_len(tokens) != 5)
		return (FALSE);
	ft_bzero(obj->s_tex.name, MAX_NAME_LEN);
	ft_strlcpy(obj->s_tex.name, tokens[1], MAX_NAME_LEN);
	if (!get_color(tokens[2], &obj->s_tex.s_checker.color1))
		return (FALSE);
	if (!get_color(tokens[3], &obj->s_tex.s_checker.color2))
		return (FALSE);
	if (!is_int(tokens[4]) && !is_float(tokens[4]))
		return (FALSE);
	obj->s_tex.s_checker.size = (float)ft_atod(tokens[4]);
	return (TRUE);
}
