/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 03:32:52 by achernys          #+#    #+#             */
/*   Updated: 2017/11/11 04:13:21 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	if ((*alst)->next == NULL)
	{
		ft_lstdelone(alst, del);
		return ;
	}
	ft_lstdel(&((*alst)->next), del);
	ft_lstdelone(alst, del);
}
