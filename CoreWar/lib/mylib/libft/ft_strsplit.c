/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:10:21 by achernys          #+#    #+#             */
/*   Updated: 2017/11/09 17:10:40 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**memfree(char **s)
{
	while (s != NULL)
	{
		ft_memdel((void **)s);
		s++;
	}
	return (NULL);
}

static char	**strcreate(char const *s, char c, int tmp, int i)
{
	int		j;
	char	**str;

	j = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			tmp += 1;
	}
	if (!(str = (char **)ft_memalloc(sizeof(char*) * (tmp + 1))))
		return (NULL);
	tmp = 0;
	while (*s != '\0')
	{
		tmp = *s != c ? tmp + 1 : tmp + 0;
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
		{
			if (!(str[j++] = (char *)ft_memalloc(sizeof(char) * (tmp + 1))))
				return (memfree(str));
			tmp = 0;
		}
		s++;
	}
	str[j] = 0;
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	char	**outsarr;

	if (s == NULL || !(outsarr = strcreate(s, c, 0, -1)))
		return (NULL);
	i = 0;
	j = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			outsarr[i][j] = *s;
			j++;
		}
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
		{
			outsarr[i][j] = '\0';
			j = 0;
			i++;
		}
		s++;
	}
	return (outsarr);
}
