/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 04:45:35 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/11 02:04:22 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_list_env **env, char *key)
{
	t_list_env	*prev;
	t_list_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->data.key, key) == 0)
		{
			if (prev == NULL) // first node
			{
				*env = curr->next;
			}
			else
			{
				prev->next = curr->next;
			}
			free_node(curr);
			g_global_exit.exit_status = 0;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	// key not found, do nothing
	g_global_exit.exit_status = 1;
}

int	main_unset(t_list_env **new_env, t_list_env **export_list, char **cmd)
{
	int	len;
	int	i;
	int	err;

	err = 0;
	len = size_cmd(cmd);
	i = 1;
	while (i < len)
	{
		if (check_key_value_isvalid_export(cmd[i]))
		{
			ft_unset(new_env, cmd[i]);
			ft_unset(export_list, cmd[i]);
		}
		else
		{
			if (cmd[i][0] == '-')
				ft_printf("minishell : unset: invalid option\n");
			else if (cmd[i][0] == '!')
				ft_printf("minishell : unset: event not found\n");
			else	
				ft_printf("minishell : unset: `%s': not a valid identifier\n", cmd[i]);
			if (cmd[i][0] != '!')
				err = 1;
		}
		i++;
	}
	if (err == 1)
		return (1);
	return (0);
}
