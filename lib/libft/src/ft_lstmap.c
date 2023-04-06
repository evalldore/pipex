/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evallee- <evallee-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:04:14 by evallee-          #+#    #+#             */
/*   Updated: 2023/02/24 18:14:22 by evallee-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*first_list;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	first_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_list = ft_lstnew(new_content);
		if (!new_list)
		{
			ft_lstclear(&first_list, del);
			del(new_content);
			return (NULL);
		}
		ft_lstadd_back(&first_list, new_list);
		lst = lst->next;
	}
	return (first_list);
}
