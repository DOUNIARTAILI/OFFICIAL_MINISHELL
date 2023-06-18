/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_args_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 08:05:15 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/18 16:41:06 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_valid(t_list_env **env, t_list_env **export_list, char *cmd)
{
	if (check_equal_existance(cmd) && !check_plus_existance(cmd))
		export_equ_only(env, export_list, cmd);
	else if (check_equal_existance(cmd) && check_plus_existance(cmd))
		export_join(env, export_list, cmd);
	else
	{
		if (get_node_by_key(export_list, cmd) != NULL)
		{
			return ;
		}
		else
		{
			add_to_export_only(export_list, cmd);
		}
	}
}
