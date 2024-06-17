/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:40:00 by flfische          #+#    #+#             */
/*   Updated: 2024/06/17 19:19:40 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO:
		- replace pointers in malloc with arrays to improve speed
*/

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

	if (DEBUG)
		atexit(leaks);
	if (argc != 2)
		return (0);
	if (!is_valid_parsing(argv[1]))
		printf("Parsing is not valid\n");
	else
		printf("Parsing is valid\n");
	if (DEBUG)
		print_objs();
	program = ft_get_program();
	if (ft_mlx_init())
		return (1);
	ft_init_rt(program);
	ft_get_first_obj(SPHERE)->material.type = CHECKER;
	ft_get_first_obj(SPHERE)->material.s_checker.color1 = 0x00FF00FF;
	ft_get_first_obj(SPHERE)->material.s_checker.color2 = 0x0000FFFF;
	ft_get_first_obj(SPHERE)->material.s_checker.size = 1;
	mlx_key_hook(program->mlx, ft_key_hook, program);
	if (program->thread_count < 2)
		mlx_loop_hook(program->mlx, ft_render, program);
	else
		mlx_loop_hook(program->mlx, ft_render_multithread, program);
	mlx_loop(program->mlx);
	join_threads(program);
	return (0);
}
