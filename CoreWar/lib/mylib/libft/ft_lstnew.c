/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 01:41:07 by achernys          #+#    #+#             */
/*   Updated: 2017/11/11 02:56:14 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *newlist;

	if (!(newlist = (t_list *)ft_memalloc(sizeof(*newlist))))
	{
		return (NULL);
	}
	if (!(newlist->content = ft_memalloc(content_size)))
	{
		ft_memdel((void *)&newlist);
		return (NULL);
	}
	if (!content)
	{
		newlist->content = NULL;
		newlist->content_size = 0;
		newlist->next = NULL;
		return (newlist);
	}
	newlist->content = ft_memcpy(newlist->content, content, content_size);
	newlist->content_size = content_size;
	newlist->next = NULL;
	return (newlist);
}
