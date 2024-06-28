/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:40:00 by flfische          #+#    #+#             */
/*   Updated: 2024/06/28 17:45:25 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_program	*ft_get_program(void)
{
	static t_program	program;

	return (&program);
}

void	leaks(void)
{
	system("leaks miniRT");
}

int	main(int argc, char **argv)
{
	t_program	*program;

	atexit(leaks);
	if (DEBUG)
		atexit(leaks);
	if (argc != 2)
		return (ft_print_error("Arguments shouldn't by empty"), 0);
	if (!is_valid_parsing(argv[1]))
		return (1);
	if (DEBUG)
		print_objs(NULL);
	program = ft_get_program();
	if (ft_mlx_init())
		return (1);
	if (!ft_assign_mat_tex())
		return (1);
	ft_init_rt(program);
	mlx_key_hook(program->mlx, ft_key_hook, program);
	if (program->thread_count < 2)
		mlx_loop_hook(program->mlx, ft_render, program);
	else
		mlx_loop_hook(program->mlx, ft_render_multithread, program);
	mlx_loop(program->mlx);
	join_threads(program);
	return (0);
}
