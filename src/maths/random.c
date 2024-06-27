/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:56:52 by flfische          #+#    #+#             */
/*   Updated: 2024/06/27 16:36:43 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Generates a random double between 0 and 1.
 *
 * @return The random double.
 */
double	ft_randf(void)
{
	return (((double)rand() / ((double)RAND_MAX) + 1.0));
}

double	ft_randf_range(double min, double max)
{
	return (min + (max - min) * ft_randf());
}
