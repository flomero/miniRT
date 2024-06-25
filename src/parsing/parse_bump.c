/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:51:02 by flfische          #+#    #+#             */
/*   Updated: 2024/06/25 17:00:53 by flfische         ###   ########.fr       */
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
	ft_bzero(obj->s_bump.name, MAX_NAME_LEN);
	ft_strlcpy(obj->s_bump.name, tokens[1], MAX_NAME_LEN);
	bzero(obj->s_bump.path, MAX_PATH_LEN);
	ft_strlcpy(obj->s_bump.path, tokens[2], MAX_PATH_LEN);
	fd = open(obj->s_bump.path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	obj->s_bump.img = mlx_load_png(obj->s_bump.path);
	if (!obj->s_bump.img)
		return (0);
	return (1);
}
