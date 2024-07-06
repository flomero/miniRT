/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:25:07 by flfische          #+#    #+#             */
/*   Updated: 2024/07/06 16:10:33 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Initializes the mlx.
 *
 * @return 0 on success, 1 on error.
 */
int	ft_mlx_init(char *filename)
{
	t_program	*program;
	char		title[100];

	ft_debug_message("Initializing mlx...");
	ft_strlcpy(title, WIN_TITLE " ", 100);
	ft_strlcat(title, filename, 100);
	program = ft_get_program();
	program->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, title, 0);
	if (!program->mlx)
		return (ft_print_error(mlx_strerror(mlx_errno)), 1);
	program->image = mlx_new_image(program->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!program->image)
		return (ft_print_error(mlx_strerror(mlx_errno)), 1);
	program->img_size.x = WIN_WIDTH;
	program->img_size.y = WIN_HEIGHT;
	if (mlx_image_to_window(program->mlx, program->image, 0, 0) == -1)
		return (ft_print_error(mlx_strerror(mlx_errno)), 1);
	ft_debug_message("Mlx initialized.");
	return (0);
}
