/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:10:03 by mouaammo          #+#    #+#             */
/*   Updated: 2023/05/20 16:09:03 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_list	*ft_lstnew(t_token *mytoken)
{
	t_list	*node;

	node = NULL;
	node = (t_list *) malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = mytoken;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
