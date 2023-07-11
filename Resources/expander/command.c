/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:23:39 by mouaammo          #+#    #+#             */
/*   Updated: 2023/07/10 13:35:12 by mouaammo         ###   ########.fr       */
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
