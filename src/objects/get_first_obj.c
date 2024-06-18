/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:13:41 by flfische          #+#    #+#             */
/*   Updated: 2024/06/18 09:47:33 by flfische         ###   ########.fr       */
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
	while (i < program->objs_len)
	{
		obj = &program->objs[i];
		if (obj->type == type)
			return (obj);
		i++;
	}
	return (NULL);
}

t_object	*ft_get_nth_obj(t_object_type type, int n)
{
	t_object	*obj;
	t_program	*program;
	int			i;
	int			count;

	program = ft_get_program();
	i = 0;
	count = 0;
	while (i < program->objs_len)
	{
		obj = &program->objs[i];
		if (obj->type == type)
		{
			if (count == n)
				return (obj);
			count++;
		}
		i++;
	}
	return (NULL);
}
