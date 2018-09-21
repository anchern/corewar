/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 04:21:26 by achernys          #+#    #+#             */
/*   Updated: 2017/11/11 05:42:00 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst == NULL || f == NULL)
		return ;
	if (lst->next == NULL)
	{
		(*f)(lst);
		return ;
	}
	(*f)(lst);
	ft_lstiter(lst->next, f);
}
