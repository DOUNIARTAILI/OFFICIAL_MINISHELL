/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 07:43:05 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/11 02:04:22 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_key_export_with_equ(char *cmd1)
{
	int	i;

	i = 0;
	if (cmd1[0] == '_' || ft_isalpha((int)cmd1[0]))
	{
		i = 1;
		while (cmd1[i] != '=' && cmd1[i] != '\0')
		{
			if ((ft_isdigit((int)cmd1[i]) || ft_isalpha((int)cmd1[i])
					|| (cmd1[i + 1] == '=' && cmd1[i] == '+') || cmd1[i] == '_')
				&& cmd1[i] != '\0')
			{
				i++;
			}
			else
				break ;
		}
		if (cmd1[i] == '=')
			return (1);
	}
	return (0);
}

int	key_check_without_equ(char *cmd1)
{
	int	i;

	i = 0;
	if (cmd1[0] == '_' || ft_isalpha((int)cmd1[0]))
	{
		i = 1;
		while (cmd1[i] != '\0')
		{
			if ((ft_isdigit((int)cmd1[i]) || ft_isalpha((int)cmd1[i])
					|| cmd1[i] == '_') && cmd1[i] != '\0')
			{
				i++;
			}
			else
				break ;
		}
		if (cmd1[i] == '\0')
			return (1);
	}
	return (0);
}

int	check_equal_existance(char *cmd1)
{
	int	i;

	i = 0;
	while (cmd1[i] != '\0')
	{
		if (cmd1[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_plus_existance(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

int	check_key_value_isvalid_export(char *cmd)
{
	int	i;

	i = 0;
	if (check_equal_existance(cmd))
	{
		if (!check_key_export_with_equ(cmd))
			return (0);
	}
	else
	{
		if (!key_check_without_equ(cmd))
			return (0);
	}
	return (1);
}