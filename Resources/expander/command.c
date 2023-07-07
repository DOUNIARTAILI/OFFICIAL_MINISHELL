/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:23:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/07/07 16:00:13 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	add_multi_nodes(t_list **origin, t_voidlst *newlist)
{
	while (newlist)
	{
		ft_lstadd_back(origin, ft_lstnew(newlist->content));
		newlist = newlist->next;
	}
}

int	is_redirect(int token)
{
	if (token == RE_APPEND || token == RE_IN
		|| token == RE_OUT || token == HERE_DOC)
		return (1);
	return (0);
}

int	get_space(char *str)
{
	int	i;
	
	i = 0;
	while (str && str[i])
	{
		if (ft_isspace(str[i]))
			return (str[i]);
		i++;
	}
	return (0);
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
		if (str_cmp(tmp_join, "$") == 0)
			tmp_join = ft_strdup("");
		join_str = ft_strjoin_1(join_str, tmp_join);
		if ((*head)->content->token == DLR && get_space(tmp_join))
			flag = 1;
		(*head) = (*head)->next;
	}
	tmp_join = join_str;
	join_str = ft_strtrim(tmp_join, " ");
	free(tmp_join);
	if (flag)
	{
		ft_printf(2, "minishell: ambiguous redirect\n");
		return (free(join_str), g_global_exit.exit_status = 1, 0);
	}
	if (join_str)
		ft_lstadd_back(newlist, ft_lstnew(new_token(join_str, mytoken)));
	return (free(join_str), 1);
}

int	handle_cmd(t_list **newlist, t_list **head, t_list_env *myenv)
{
	int		mytoken;

	while ((*head))
	{
		mytoken = (*head)->content->token;
		if (is_redirect(mytoken))
		{
			if (mytoken == HERE_DOC)
			{
				if (!handle_heredoc(newlist, head, myenv))
					return (0);
			}
			else
			{
				if (!handle_redirection(newlist, head, myenv, mytoken))
					return (0);
			}
		}
		else
		{
			command_expansion(newlist, head, myenv);
			(*head) = (*head)->next;
		}
	}
	return (1);
}

t_cmds	*node_collecter(t_cmds args)
{
	t_cmds	*new_collecter;

	new_collecter = malloc (sizeof (t_cmds));
	if (!new_collecter)
		return (NULL);
	new_collecter->commands = args.commands;
	new_collecter->redirects = args.redirects;
	return (new_collecter);
}
