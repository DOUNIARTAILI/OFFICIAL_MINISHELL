/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 01:58:27 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/11 02:04:22 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *cmd)
{
	int	i;
	int	len;

	i = 2;
	len = ft_strlen(cmd);
	if (cmd[0] == '-' && cmd[1] == 'n')
	{
		while (cmd[i] == 'n' && cmd[i])
			i++;
		if (i < len)
			return (0);
	}
	else
		return (0);
	return (1);
}

void	echo_printer(int i, char **cmd)
{
	while (cmd[i] != NULL)
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1] !=NULL)
			ft_printf(" ");
		i++;
	}
}

// int	ft_echo(char **cmd)
// {
// 	int	i;

// 	if (!cmd[1])
// 		ft_printf("\n");
// 	else if (!ft_strcmp(cmd[1], "-n") || check_n(cmd[1]))
// 	{
// 		i = 2;
// 		echo_printer(i, cmd);
// 	}
// 	else
// 	{
// 		i = 1;
// 		echo_printer(i, cmd);
// 		ft_printf("\n");
// 	}
// 	return (0);
// }

int	skip_n(char **cmd)
{
	int	i;

	i = 2;
	while (cmd[i] != NULL)
	{
		if (check_n(cmd[i]))
			i++;
		else
		{
			return (i);
		}
	}
	return (-1);
}

int	ft_echo(char **cmd)
{
	int	i;

	if (!cmd[1])
		ft_printf("\n");
	else if (!ft_strcmp(cmd[1], "-n") || check_n(cmd[1]))
	{
		i = skip_n(cmd);
		echo_printer(i, cmd);
	}
	else
	{
		i = 1;
		echo_printer(i, cmd);
		ft_printf("\n");
	}
	return (0);
}
