/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:42:34 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/19 21:36:49 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_env	*ft_lstlast_node(t_list_env *lst)
{
	t_list_env	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_list_env	*ft_lstnew_node(t_env content)
{
	t_list_env	*node;

	node = malloc(sizeof(t_list_env));
	if (!node)
		return (NULL);
	node->data.key = ft_strdup(content.key);
	node->data.value = ft_strdup(content.value);
	node->next = NULL;
	return (node);
}

void	add_back_to_list(t_list_env **lst, t_list_env *new)
{
	t_list_env	*last;

	if (!lst)
		return ;
	last = ft_lstlast_node(*lst);
	if (last == NULL)
		*lst = new;
	else
		last->next = new;
}
