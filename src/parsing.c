/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:15:15 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/09 13:28:25 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief does the whole parsing, that consists of these:
 * 1. checking filename if end with .rt
 * 2. checking if file is not empty or only empty lines
 * 3. check if all mandadory object occurs exact 1 time A, C, L
 * 4. takes every object and initilize it in a struct
 *
 * @param fname name of the file to parse
 * @return int 0 in case of error, 1 otherwise
 */
int	is_valid_parsing(char *fname)
{
	int	len;

	if (!fname || ft_strlen(fname) < 4)
		return (ft_print_error("Not valid filename"), 0);
	len = ft_strlen(fname);
	if (fname[len - 1] != 't' || fname[len - 2] != 'r' || fname[len - 3] != '.')
		return (ft_print_error("Not valid filename"), 0);
	len = get_nbr_of_lines(fname);
	if (len == 0)
		return (ft_print_error("Empty file"), 0);
	// TODO init struct
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

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		line = ft_strjoin("Error opening file: ", strerror(errno));
		ft_print_error(line);
		return (free(line), -1);
	}
	line = get_next_line(fd);
	count = 0;
	while(line)
	{
		if (!(line[0] == '\n' && !line[1]))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
	{
		line = ft_strjoin("Error closing file: ", strerror(errno));
		ft_print_error(line);
		return (free(line), -1);
	}
	return (count);
}

int	init_struct(char *fname, int len)
{
	t_object **objs;
	int		i;
	char	*line;
	int		fd;

	objs = malloc(sizeof(t_object *) * len);
	if (!objs)
		return (ft_print_error("Memory allocation failed"), -1);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		line = ft_strjoin("Error opening file: ", strerror(errno));
		ft_print_error(line);
		return (free(line), -1);
	}
	line = get_next_line(fd);
	i = 0;
	while(line)
	{
		if (!(line[0] == '\n' && !line[1]))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		objs[i] = get_obj(line);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
	{
		line = ft_strjoin("Error closing file: ", strerror(errno));
		ft_print_error(line);
		return (free(line), -1);
	}
	return (0);
}

t_object	*get_obj(char *line)
{
	char		**tokes;
	// t_object	*obj;

	tokes = ft_split(line, ' ');
	return (NULL);
}
