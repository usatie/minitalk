/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 23:02:10 by susami            #+#    #+#             */
/*   Updated: 2022/05/26 23:01:07 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// Returns the NULL or c terminated length of the str.
static size_t	strclen(char *str, char sep)
{
	int	cnt;

	cnt = 0;
	while (*str && *str != sep)
	{
		cnt++;
		str++;
	}
	return (cnt);
}

// The strndup() function copies at most n characters from the string s1
// always NUL terminating the copied string.
static char	*ft_strndup(char *src, int size)
{
	int		len;
	char	*new;

	len = ft_strlen(src);
	if (len > size)
		len = size;
	new = ft_calloc(len + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_memmove(new, src, len);
	return (new);
}

// RETURN VALUE
// 		Size of the array needed to split str with c.
static size_t	get_array_size(char *str, char c)
{
	int		array_size;

	array_size = 1;
	while (*str)
	{
		if (strclen(str, c) > 0)
		{
			array_size++;
			str += strclen(str, c);
		}
		else
			str++;
	}
	return (array_size);
}

// RETURN VALUE
// 		The array splitted str with c.
// 		Example1.
//	 		str: "Hello,World,Shun"
// 			c: ','
// 			arr_size: 4
// 			arr: {"Hello", "World", "Shun", NULL}
// 		Example2.
//	 		str: ",,,Continuous,,commas,,,will,,be,,ignored,"
// 			c: ','
// 			arr_size: 6
// 			arr: {"Continuous, "commas", "will", "be", "ignored", NULL}
// 		EXAMPLE3:
// 			str: ""
// 			c: ','
// 			arr_size: 1
// 			arr: {NULL}
//
//
// s: not protected
char	**ft_split(char *s, char c)
{
	char	**arr;
	int		i;

	arr = ft_calloc(get_array_size(s, c), sizeof(char *));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (strclen(s, c) > 0)
		{
			arr[i] = ft_strndup(s, strclen(s, c));
			if (arr[i++] == NULL)
			{
				while (i)
					free(arr[--i]);
				free(arr);
				return (NULL);
			}
			s += strclen(s, c);
		}
		else
			s++;
	}
	return (arr);
}
