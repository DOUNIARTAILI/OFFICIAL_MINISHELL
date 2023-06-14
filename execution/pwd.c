/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:37:56 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/14 20:11:04 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_list_env **env)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("%s\n", get_value_of_key(env, "PWD"));
	else
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
	return (1);
}
