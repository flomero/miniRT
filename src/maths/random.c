/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:56:52 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 11:57:59 by flfische         ###   ########.fr       */
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
	return ((float)rand() / (float)RAND_MAX);
}
