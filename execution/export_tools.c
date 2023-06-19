/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 07:58:37 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/19 21:16:32 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_env	*env_dup_node(t_env data)
{
	t_list_env	*node;

	node = malloc(sizeof(t_list_env));
	node->data.key = ft_strdup(data.key);
	node->data.value = ft_strdup(data.value);
	node->next = NULL;
	return (node);
}

t_list_env	*env_dup(t_list_env *env)
{
	t_list_env	*tmp;
	t_list_env	*dup;
	t_list_env	*dup_tail;
	int			i;

	tmp = env;
	dup = NULL;
	i = -1;
	while (++i < env_size(env))
	{
		if (dup == NULL)
		{
			dup = env_dup_node(tmp->data);
			dup_tail = dup;
		}
		else
		{
			dup_tail->next = env_dup_node(tmp->data);
			dup_tail = dup_tail->next;
		}
		tmp = tmp->next;
	}
	return (dup);
}

int	when_key_ends(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '=')
		{
			return (i);
			break ;
		}
		i++;
	}
	return (0);
}

char	**key_value_of_arg(char *cmd)
{
	char	**key_value;
	int		index_key_end;	
	int		k;
	int		i;

	index_key_end = when_key_ends(cmd);
	key_value = (char **)malloc(sizeof(char *) * (2 + 1));
	if (!key_value)
		return (NULL);
	i = 0;
	k = 0;
	while (k < 2)
	{
		key_value[k] = ft_substr(cmd, i, index_key_end);
		if (check_equal_existance(cmd) && check_plus_existance(cmd) && (k == 0))
			key_value[k] = ft_substr(cmd, i, (index_key_end - 1));
		if (!key_value[k])
		{
			return (NULL);
		}
		i = index_key_end + 1;
		index_key_end = ft_strlen(cmd) - (index_key_end + 1);
		k++;
	}
	return (key_value);
}
