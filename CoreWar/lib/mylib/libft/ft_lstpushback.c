/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 19:42:11 by achernys          #+#    #+#             */
/*   Updated: 2017/11/13 19:42:44 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **alst, t_list *newlist)
{
	if ((*alst)->next == NULL)
	{
		(*alst)->next = newlist;
		return ;
	}
	ft_lstpushback(&((*alst)->next), newlist);
}
