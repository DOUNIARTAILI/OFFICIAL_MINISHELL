/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:20:20 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/11 20:18:00 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_env	*split_key_value(char *env)
{
	char	**split;
	t_env	*key_value;

	key_value = malloc (sizeof (t_env));
	if (!key_value)
		return (NULL);
	split = ft_split(env, '=');
	key_value->key = ft_strdup(split[0]);
	key_value->value = ft_substr(env, ft_strlen(split[0]) + 1, ft_strlen(env));
	free_all(split);
	return (key_value);
}

char	*search_for_key(char *str, t_list_env *myenv)
{
	t_env	keyval_env;

	while (myenv)
	{
		keyval_env = myenv->data;
		if (str_cmp(str, keyval_env.key) == 0)
			return (keyval_env.value);
		myenv = myenv->next;
	}
	return (NULL);
}
