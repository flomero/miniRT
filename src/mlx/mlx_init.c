/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:25:07 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 14:00:32 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Initializes the mlx.
 *
 * @return 0 on success, 1 on error.
 */
int	ft_mlx_init(void)
{
	t_program	*program;

	program = ft_get_program();
	program->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, 0);
	if (!program->mlx)
		return (ft_print_error(mlx_strerror(mlx_errno)), 1);
	program->image = mlx_new_image(program->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!program->image)
		return (ft_print_error(mlx_strerror(mlx_errno)), 1);
	program->img_size.x = WIN_WIDTH;
	program->img_size.y = WIN_HEIGHT;
	if (mlx_image_to_window(program->mlx, program->image, 0, 0) == -1)
		return (ft_print_error(mlx_strerror(mlx_errno)), 1);
	return (0);
}
