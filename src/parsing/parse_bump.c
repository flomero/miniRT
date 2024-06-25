/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:51:02 by flfische          #+#    #+#             */
/*   Updated: 2024/06/21 14:58:56 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Get the bump object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
t_bool	get_bump(char **tokens, t_object *obj)
{
	int	fd;

	obj->type = BUMP;
	if (get_arr_len(tokens) != 3)
		return (0);
	obj->s_bump.name = ft_strdup(tokens[1]);
	if (!obj->s_bump.name)
		return (0);
	obj->s_bump.path = ft_strdup(tokens[2]);
	if (!obj->s_bump.path)
		return (0);
	fd = open(obj->s_bump.path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	obj->s_bump.img = mlx_load_png(obj->s_bump.path);
	if (!obj->s_bump.img)
		return (0);
	return (1);
}
