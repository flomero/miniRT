/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:56:51 by flfische          #+#    #+#             */
/*   Updated: 2024/06/07 15:02:19 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// TODO: free stuff on exit
void	ft_key_hook(void *param)
{
	t_program	*program;

	program = (t_program *)param;
	if (mlx_is_key_down(program->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(program->mlx);
		exit(0);
	}
}
