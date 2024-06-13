/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:55:21 by flfische          #+#    #+#             */
/*   Updated: 2024/06/13 12:43:08 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdint.h>

t_color	ft_color_color_add(t_color color1, t_color color2)
{
	t_color	fcolor;

	fcolor.r = color1.r + color2.r;
	fcolor.g = color1.g + color2.g;
	fcolor.b = color1.b + color2.b;
	fcolor.r = ft_color_clamp(fcolor.r);
	fcolor.g = ft_color_clamp(fcolor.g);
	fcolor.b = ft_color_clamp(fcolor.b);
	return (fcolor);
}
