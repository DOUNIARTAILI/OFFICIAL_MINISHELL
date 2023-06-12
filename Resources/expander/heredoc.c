/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:16:04 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/12 21:48:28 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	concate_in_heredoc(t_list **head, int *flag, char **delemiter)
{
	*delemiter = NULL;
	(*head) = (*head)->next;
	while ((*head) && (*head)->content->token != ESP
		&& !is_redirect((*head)->content->token))
	{
		if ((*head)->content->token == QUOTE
			|| (*head)->content->token == S_QUOTE)
			*flag = 1;
		*delemiter = ft_strjoin_1(*delemiter, ft_strdup((*head)->content->str));
		(*head) = (*head)->next;
	}
	*delemiter = ft_strjoin_1(*delemiter, ft_strdup("\n"));
}

void	manage_heredoc(t_list **head, int *fd, t_list_env *myenv)
{
	char	*delemiter;
	char	*line;
	char	*buffer;
	int		flag;

	buffer = NULL;
	flag = 0;
	concate_in_heredoc(head, &flag, &delemiter);
	g_global_exit.heredoc = 1;
	while (1)
	{
		// ft_putstr_fd("heredoc> ", 1);
		// line = get_next_line(g_global_exit.heredoc);
		line = readline("heredoc> ");
		// if (!g_global_exit.heredoc)
		// 	return;
		if (!line || !str_cmp(line, delemiter))
		{
			free(delemiter);
			if (buffer)
				write(*fd, buffer, ft_strlen(buffer));
			free(buffer);
			break ;
		}
		if (ft_strchr(line, '$') && !flag)
			line = replace_all(line, myenv);
		buffer = ft_strjoin_1(buffer, line);
	}
}

int	handle_heredoc(t_list **newlist, t_list **head, t_list_env *myenv)
{
	char		*str;
	int			fd;
	char		*int_str;
	static int	i;

	int_str = ft_itoa(i++);
	str = ft_strjoin_1(ft_strdup("/tmp/file"), int_str);
	fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		printf("❌❌ bad file descriptor\n");
		return (0);
	}
	manage_heredoc(head, &fd, myenv);
	close (fd);
	if (!g_global_exit.heredoc)
		return 1;
	ft_lstadd_back(newlist, ft_lstnew(new_token(str, RE_IN)));
	return (1);
}
