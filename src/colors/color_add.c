/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:55:21 by flfische          #+#    #+#             */
/*   Updated: 2024/06/14 12:13:53 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdint.h>

t_color	*ft_color_color_add(t_color color1, t_color color2, t_color *result)
{
	result->r = color1.r + color2.r;
	result->g = color1.g + color2.g;
	result->b = color1.b + color2.b;
	result->r = ft_color_clamp(result->r);
	result->g = ft_color_clamp(result->g);
	result->b = ft_color_clamp(result->b);
	return (result);
}
