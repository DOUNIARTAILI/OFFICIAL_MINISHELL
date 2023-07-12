/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:34:44 by mouaammo          #+#    #+#             */
/*   Updated: 2023/07/12 22:46:11 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	myfunc(t_list **newlist, char **join_str, int flag, int mytoken)
{
	char	*tmp_join;

	tmp_join = *join_str;
	*join_str = ft_strtrim(tmp_join, " ");
	if (flag || !ft_strlen(tmp_join))
	{
		ft_printf(1, "minishell: ambiguous redirect\n");
		g_global_exit.exit_status = 1;
		mytoken = 0;
	}
	free(tmp_join);
	ft_lstadd_back(newlist, ft_lstnew(new_token(*join_str, mytoken)));
}

int	handle_redirection(t_list **newlist,
	t_list **head, t_list_env *myenv, int mytoken)
{
	char	*join_str;
	char	*tmp_join;
	int		flag;

	join_str = NULL;
	flag = 0;
	(*head) = (*head)->next;
	while ((*head) && (*head)->content->token != ESP
		&& (*head)->content->token != PIPE
		&& !is_redirect((*head)->content->token))
	{
		if ((*head)->content->token == DLR || (*head)->content->token == QUOTE)
			tmp_join = replace_all(ft_strdup((*head)->content->str), myenv);
		else
			tmp_join = ft_strdup((*head)->content->str);
		if ((*head)->content->token == DLR && get_space(tmp_join))
			flag = 1;
		join_str = ft_strjoin_1(join_str, tmp_join);
		(*head) = (*head)->next;
	}
	myfunc(newlist, &join_str, flag, mytoken);
	return (free(join_str), 1);
}
