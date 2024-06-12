/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:56:52 by flfische          #+#    #+#             */
/*   Updated: 2024/06/11 16:10:35 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Generates a random float between 0 and 1.
 *
 * @return The random float.
 */
float	ft_randf(void)
{
	return (((float)rand() / ((float)RAND_MAX) + 1.0));
}

float	ft_randf_range(float min, float max)
{
	return (min + (max - min) * ft_randf());
}
