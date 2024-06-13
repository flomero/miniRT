/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 22:46:57 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/13 11:57:48 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief free an NULL terminated array of char pointers properly
 * ex. arr = ["El1", "el2", NULL]
 *
 * @param arr
 */
void	free_str_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

// /**
//  * @brief free an NULL terminated array of t_object pointers properly
//  * ex. arr = ["El1", "el2", NULL]
//  *
//  * @param arr
//  */
// void	free_obj_arr(t_object **arr)
// {
// 	int	i;

// 	i = -1;
// 	while (arr[++i])
// 		free(arr[i]);
// 	free(arr);
// }

/**
 * @brief Get the cy object
 *
 * @param tokens
 * @param obj
 * @return int 1 on success, 0 otherwise
 */
int	get_cy(char **tokens, t_object *obj)
{
	obj->type = CYLINDER;
	if (get_arr_len(tokens) != 6)
		return (free(obj), 0);
	if (!get_vector(&obj->pos, tokens[1]))
		return (free(obj), 0);
	if (!get_vector(&obj->s_cylinder.normal, tokens[2]))
		return (free(obj), 0);
	if (!in_range(&obj->s_cylinder.normal, -1, 1))
		return (free(obj), 0);
	if (!is_float(tokens[3]) && !is_int(tokens[3]))
		return (free(obj), 0);
	obj->s_cylinder.diameter = (float)ft_atod(tokens[3]);
	if (!is_float(tokens[4]) && !is_int(tokens[4]))
		return (free(obj), 0);
	obj->s_cylinder.height = (float)ft_atod(tokens[4]);
	if (!get_color(tokens[5], &obj->color))
		return (free(obj), 0);
	return (1);
}

/**
 * @brief Get the nbr of lines, count how many lines there are in a file,
 * skipping empty lines
 *
 * @param fname the file which will read and count how many lines it contains
 * @return int -1 if its an error opening-closing file, nbr of lines otherwise
 */
int	get_nbr_of_lines(char *fname)
{
	char	*line;
	int		count;
	int		fd;
	char	**tokens;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (print_err_extend("Error opening file: ", strerror(errno)), -1);
	line = get_next_line(fd);
	count = 0;
	while (line)
	{
		tokens = ft_multi_split(line, " \t");
		if (!((line[0] == '\n' && !line[1]) || !tokens || !tokens[0]))
			count++;
		free(line);
		if (tokens)
			free_str_arr(tokens);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
		return (print_err_extend("Error closing file: ", strerror(errno)), -1);
	return (count);
}

/**
 * @brief combine three integers [0-255] to one uint32_t number
 *
 * @param red
 * @param green
 * @param blue
 * @return uint32_t
 */
uint32_t	int_to_rgb(int red, int green, int blue)
{
	uint32_t	color;

	color = 0;
	color |= (uint32_t)red << 24;
	color |= (uint32_t)green << 16;
	color |= (uint32_t)blue << 8;
	color |= 0xFF;
	return (color);
}
