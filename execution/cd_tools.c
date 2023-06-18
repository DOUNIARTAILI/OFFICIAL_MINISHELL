/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:24:31 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/18 16:25:05 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	look_for_key(char *str, t_list_env **env)
{
	t_list_env	*ev;

	ev = *env;
	while (ev)
	{
		if (ft_strcmp(str, ev->data.key) == 0)
			return (0);
		ev = ev->next;
	}
	return (1);
}

int	cd_only(t_list_env **env)
{
	if (look_for_key("HOME", env))
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	else if (!look_for_key("HOME", env)
		&& !ft_strcmp(get_value_of_key(env, "HOME"), "\0"))
	{
		return (0);
	}
	else if (chdir(get_value_of_key(env, "HOME")) == -1)
		perror("minishell");
	return (1);
}
