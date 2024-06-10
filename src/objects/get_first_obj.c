/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:13:41 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 17:21:12 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Gets the first object in the list of specified type in the program.
 *
 * @param objs The list of objects.
 * @param type The type of object to get.
 * @return The next object.
 */
t_object	*ft_get_first_obj(t_object_type type)
{
	t_object	*obj;
	t_program	*program;
	int			i;

	program = ft_get_program();
	i = 0;
	while (i < program->object_count)
	{
		obj = &program->objects[i];
		if (obj->type == type)
			return (obj);
		i++;
	}
	return (NULL);
}
