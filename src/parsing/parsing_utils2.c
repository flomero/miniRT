/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamprak <klamprak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:32:02 by klamprak          #+#    #+#             */
/*   Updated: 2024/06/09 16:50:22 by klamprak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief checks if str is a sequence of digits and nothing else
 *
 * @param str
 * @return int 1 if it contains only digits, 0 otherwise
 */
int	is_int(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

/**
 * @brief checks if str contains only digits and a '.' in between
 *
 * @param str
 * @return int 1 if it match the case, 0 otherwise
 */
int	is_float(char *str)
{
	int		i;
	char	**parts;

	if (ft_strnstr(str, "..", ft_strlen(str)))
		return (0);
	parts = ft_split(str, '.');
	if (get_arr_len(parts) != 2)
		return (free_str_arr(parts), 0);
	if (!is_int(parts[0]) || !is_int(parts[1]))
		return (free_str_arr(parts), 0);
	return (free_str_arr(parts), 1);
}

