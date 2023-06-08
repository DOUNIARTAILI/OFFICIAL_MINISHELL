/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 04:48:36 by drtaili           #+#    #+#             */
/*   Updated: 2023/05/20 18:17:29 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_env	*fill_node_with_data(char **my_env)
{
	t_list_env	*node;

	node = malloc(sizeof(t_list_env));
	if (!node)
		return (NULL);
	node->data.key = my_env[0];
	node->data.value = my_env[1];
	node->next = NULL;
	return (node);
}

t_list_env	*get_env(char **env)
{
	t_list_env	*new_env;
	t_list_env	*curr_env;
	t_list_env	*node;
	char		**my_env;
	int			i;

	i = 0;
	new_env = NULL;
	curr_env = NULL;
	while (env[i] != NULL)
	{
		my_env = ft_split(env[i], '=');
		node = fill_node_with_data(my_env);
		if (curr_env)
			curr_env->next = node;
		else
			new_env = node;
		curr_env = node;
		i++;
	}
	return (new_env);
}

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
	node->data.key = content.key;
	node->data.value = content.value;
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
