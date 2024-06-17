/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:10:43 by flfische          #+#    #+#             */
/*   Updated: 2024/06/17 16:14:47 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_default_material(t_material *material)
{
	material->specular = DEFAULT_SPECULAR;
	material->shininess = DEFAULT_SHININESS;
	material->diffuse = DEFAULT_DIFFUSE;
	material->reflectivness = DEFAULT_REFLECTIVNESS;
}

void	ft_compute_if_reflective(t_material *material)
{
	if (material->reflectivness > 0)
	{
		material->diffuse = (1 - material->reflectivness) * DEFAULT_DIFFUSE;
		material->specular = material->reflectivness * DEFAULT_SPECULAR;
	}
}
