/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flfische <flfische@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 07:51:20 by klamprak          #+#    #+#             */
/*   Updated: 2024/07/06 19:13:13 by flfische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_multi_count_substr(char const *s, char *del)
{
	size_t	count;
	size_t	i;
	int		was_del;

	i = 0;
	count = 0;
	was_del = 1;
	while (s[i])
	{
		if (!ft_strchr(del, s[i]))
		{
			if (was_del)
				count++;
			was_del = 0;
		}
		else
			was_del = 1;
		i++;
	}
	return (count);
}

/**
 * @brief Allocates (with malloc(3)) and returns a copy of the string 'src'
 * up to the first occurrence of the delimiter character 'del'.
 * The copy is NULL-terminated.
 * If the delimiter character is not found, the entire source string is copied.
 * @param src The string to copy.
 * @param set The delimiter character.
 * @return The new string. NULL if the allocation fails.
 */
static char	*ft_multi_strdeldup(const char *src, char *set)
{
	char	*dest;
	char	del;
	char	*tmp;

	tmp = (char *)src;
	while (*tmp && !ft_strchr(set, *tmp))
		tmp++;
	del = *(ft_strchr(set, *tmp));
	dest = (char *)malloc(ft_strdellen(src, del) + 1);
	if (dest == NULL)
		return (ft_print_error(strerror(errno)), NULL);
	ft_strdelcpy(dest, src, del);
	return (dest);
}

/**
 * @brief Allocates (with malloc(3)) and returns an array of strings obtained by
 * splitting ’s’ using the character ’c’ as a delimiter. The array must be
 * ended by a NULL pointer.
 * @param s The string to split.
 * @param c The delimiter character set.
 * @return The array of new strings resulting from the split.
 */
char	**ft_multi_split(char const *s, char *set)
{
	size_t	str_count;
	size_t	i;
	char	**arr;

	str_count = ft_multi_count_substr(s, set);
	arr = malloc((str_count + 1) * sizeof(char *));
	if (arr == NULL)
		return (ft_print_error(strerror(errno)), NULL);
	i = 0;
	while (i < str_count)
	{
		while (ft_strchr(set, *s) && *s)
			s++;
		arr[i] = ft_multi_strdeldup(s, set);
		if (arr[i] == NULL)
		{
			while (i > 0)
				free(arr[--i]);
			free(arr);
			return (NULL);
		}
		s += ft_strlen(arr[i++]);
	}
	arr[i] = NULL;
	return (arr);
}
