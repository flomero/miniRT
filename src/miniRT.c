/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:40:00 by flfische          #+#    #+#             */
/*   Updated: 2024/06/10 22:55:48 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	TODO:
		- replace tabs with spaces right before parsing(now we dont handle them)
		- replace pointers in malloc with arrays to improve speed
		- double check to point I replace \n with \0 after get_next_line()(\n\n)
*/

#include "miniRT.h"

t_program	*ft_get_program(void)
{
	static t_program	program;

	return (&program);
}

void	leaks(void)
{
	system ("leaks miniRT");
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
	if (DEBUG)
		exit(0);
	program = ft_get_program();
	if (ft_mlx_init())
		return (1);
	mlx_loop_hook(program->mlx, ft_key_hook, program);
	mlx_loop(program->mlx);
	return (0);
}
