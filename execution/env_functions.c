/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 04:48:36 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/18 17:59:35 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_list_env	*build_node(char *key, char *value)
{
	t_list_env	*node;

	node = malloc(sizeof(t_list_env));
	if (!node)
		return (NULL);
	node->data.key = key;
	node->data.value = value;
	node->next = NULL;
	return (node);
}

void	update_shelvl(t_list_env *new_env)
{
	int	nb;

	nb = 0;
	if (get_value_of_key(&new_env, "SHLVL") != NULL)
	{
		nb = ft_atoi(get_value_of_key(&new_env, "SHLVL"));
		nb++;
		set_value_of_key(&new_env, "SHLVL", ft_itoa(nb));
	}
	else
		add_back_to_list(&new_env, build_node("SHLVL", ft_itoa(1)));
}

void	env_removed(t_list_env *node, t_list_env *curr_env, int j)
{
	if (j == 3)
	{
		node = build_node("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		curr_env->next = node;
	}
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
	env_removed(node, curr_env, i);
	update_shelvl(new_env);
	return (new_env);
}
