/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_and_dbdollar.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:21:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/10 04:21:54 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"
#include "../../minishell.h"

char	*exit_status_value(char **string_key, int *index)
{
	char	*string_value;

	string_value = NULL;
	string_value = ft_itoa(global_exit.exit_status);
	free(*string_key);
	*string_key = ft_strdup("$?");
	(*index)++;
	return (string_value);
}

char	*get_string_value(char *old_str, int *index,
							char **string_key, t_voidlst *myenv)
{
	char		*string_value;

	(*string_key) = NULL;
	string_value = NULL;
	(*string_key) = var_string(old_str, (*index), (*index));
	if (old_str[(*index) + 1] == '?')
		string_value = exit_status_value(string_key, index);
	else if (*string_key[0] == '$' && ft_strlen(*string_key) == 1
		&& old_str[(*index) + 1] == '$')
	{
		string_value = ft_strdup("$");
		(*index)++;
	}
	else
		string_value = search_for_key(*string_key + 1, myenv);
	return (string_value);
}
