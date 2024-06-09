/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:28:34 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/09 16:56:23 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_arr_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

uint32_t	int_to_rgb(int red, int green, int blue)
{
	return ((uint32_t)red << 16) | ((uint32_t)green << 8) | (uint32_t)blue;
}

/**
 * @brief free an NULL terminated array of char pointers properly
 * ex. arr = ["El1", "el2", NULL]
 *
 * @param arr
 */
void	free_str_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

/**
 * @brief free an NULL terminated array of t_object pointers properly
 * ex. arr = ["El1", "el2", NULL]
 *
 * @param arr
 */
void	free_obj_arr(t_object **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

// void	print_rgb(uint32_t color)
// {
// 	uint8_t red = (color >> 16) & 0xFF;
// 	uint8_t green = (color >> 8) & 0xFF;
// 	uint8_t blue = color & 0xFF;
// 	printf("RGB(%d, %d, %d)\n", red, green, blue);
// }
