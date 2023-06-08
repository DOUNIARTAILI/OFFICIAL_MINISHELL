/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 01:40:23 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/08 05:25:57 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Resources/libft/libft.h"

// -----> MOUAD <-------

#include "Resources/parsing.h"

void	display(t_voidlst *h_list)
{
	int i = 1;
	while (h_list)
	{
		t_cmds *tmp = h_list->content;
		t_voidlst	*cmds = tmp->commands;
		t_voidlst	*redirs = tmp->redirects;
		printf("command: %d\n", i);
		while (cmds)
		{
			t_token *token1 = cmds->content;
			printf("\t[%s]  token: %d\n", token1->str, token1->token);
			cmds = cmds->next;
		}
		printf("\nredirects\n");
		while (redirs)
		{
			t_token *mytoken1 = redirs->content;
			printf("\t[%s]  token: [%d]\n", mytoken1->str, mytoken1->token);
			redirs = redirs->next;
		}
		printf("\n");
		i++;
		h_list = h_list->next;
	}
}

void	display_args(t_voidlst *h_list)
{
	int i = 1;
	while (h_list)
	{
		t_command *tmp = h_list->content;
		char		**cmds = tmp->args;
		t_voidlst	*redirs = tmp->redirections;
		printf("command: %d\n", i);
		while (*cmds)
		{
			printf("\t{%s}\n", *cmds);
			cmds++;
		}
		printf("\nredirects\n");
		while (redirs)
		{
			t_token *mytoken1 = redirs->content;
			printf("\t[%s]  token: [%d]\n", mytoken1->str, mytoken1->token);
			redirs = redirs->next;
		}
		printf("\n");
		i++;
		h_list = h_list->next;
	}
}

void	leaks (void)
{
	system("leaks minishell");
}

void	affiche(t_list *head)
{
	while (head)
	{
		printf("[%s] == token [%d]\n", head->content->str, head->content->token);
		head = head->next;
	}
}

char	*concate_strings(t_list **command)
{
	t_token		*mytoken1;
	char		*join;

	join = NULL;
	while ((*command) && (mytoken1 = (*command)->content) && is_word(mytoken1->token))
	{
		join = ft_strjoin(join, ft_strdup(mytoken1->str));
		(*command) = (*command)->next;
	}
	if (is_redirect(mytoken1->token))
		(*command) = (*command)->prev;
	return (join);
}

int	fill_mylist(t_list **expander, t_cmds **mynode_cmd)
{
	t_token		*mytoken;
	char		*concate_str;

	*mynode_cmd = node_collecter((t_cmds){NULL, NULL});
	if (!*mynode_cmd)
		return (0);
	while ((*expander) && (*expander)->content->token != PIPE)
	{
		mytoken = (*expander)->content;
		if (is_word(mytoken->token) || mytoken->token == ESP)
		{
			if ((concate_str = concate_strings(expander)))
			{
				add_back(&((*mynode_cmd)->commands), new_node(new_token(concate_str, WORD)));
				free(concate_str);
			}
			else
				add_back(&((*mynode_cmd)->commands), new_node(new_token(mytoken->str, mytoken->token)));
		}
		else
			add_back(&((*mynode_cmd)->redirects), new_node(new_token(mytoken->str, mytoken->token)));
		if ((*expander))
			(*expander) = (*expander)->next;
	}
	return (1);
}

t_voidlst	*bash_concate(t_list *expander)
{
	t_cmds		*mynode_cmd;
	t_voidlst	*parent_list;
	t_list		*tmp;

	mynode_cmd = NULL;
	parent_list = NULL;
	tmp = expander;
	while (expander)
	{
		if (!fill_mylist(&expander, &mynode_cmd))
			return (NULL);
		add_back(&parent_list, new_node(mynode_cmd));
		if (expander && expander->content->token == PIPE)
			expander = expander->next;
	}
	return (/*free_linked_list(tmp),*/ parent_list);
}

t_command	*allocate_my_command(t_voidlst	*cmds)
{
	t_command	*mycommand;
	int			size;
	t_token		*mytoken;
	int			i;

	mycommand = malloc (sizeof (t_command));
	if (!mycommand)
		return (NULL);
	size = list_size(cmds);
	mycommand->args = malloc (sizeof (char *) * (size + 1));
	if (!mycommand->args)
		return (NULL);
	i = 0;
	while (cmds)
	{
		mytoken = cmds->content;
		if (mytoken && mytoken->token != ESP)
			mycommand->args[i++] = ft_strdup(mytoken->str);
		cmds = cmds->next;
	}
	mycommand->args[i] = NULL;
	return (mycommand);
}

void	free_voidlst(t_voidlst	*list)
{
	t_voidlst	*tmp;
	t_token		*mytoken;

	while (list)
	{
		mytoken = list->content;
		tmp = list->next;
		// free(mytoken->str);
		free(mytoken);
		free(list);
		list = tmp;
	}
}

void	free_big_list(t_voidlst	*biglist)
{
	t_cmds		*tmp;
	t_voidlst	*cmds;
	t_voidlst	*redirs;
	t_voidlst	*temp_list;

	while (biglist)
	{
		tmp = biglist->content;
		cmds = tmp->commands;
		redirs = tmp->redirects;
		temp_list = biglist->next;

		free_voidlst(cmds);
		free_voidlst(redirs);
		free(tmp);
		free(biglist);

		biglist = temp_list;
	}
}

t_voidlst	*parse_to_args(t_voidlst *h_list)
{
	t_cmds		*tmp;
	t_voidlst	*cmds;
	t_voidlst	*redirs;
	t_command	*mycommand;
	t_voidlst	*new_list;
	t_token		*mytoken;
	t_voidlst	*temp_list;

	new_list = NULL;
	temp_list = h_list;
	while (h_list)
	{
		tmp = h_list->content;
		cmds = tmp->commands;
		redirs = tmp->redirects;
		if (!(mycommand = allocate_my_command(cmds)))
			return (NULL);
		mycommand->redirections = NULL;
		if (!redirs)
			mycommand->redirections = NULL;
		while (redirs)
		{
			mytoken = redirs->content;
			add_back(&mycommand->redirections, new_node(new_token(mytoken->str, mytoken->token)));
			redirs = redirs->next;
		}
		add_back(&new_list, new_node(mycommand));
		h_list = h_list->next;
	}
	return (free_big_list(temp_list), new_list);
}

void	free_myenv(t_voidlst *list)
{
	t_voidlst	*tmp;
	t_env		*myenv;

	while (list)
	{
		myenv = list->content;
		tmp = list->next;
		free(myenv->key);
		free(myenv->value);
		free(myenv);
		free(list);
		list = tmp;
	}
}

// -----> MOUAD <-------

void init_glob(t_exit *glob)
{
	int i = -1;
	glob->killed = 0;
	glob->exit_status = 0;
	while (++i < 1024)
		glob->pid[i] = 0;
}

void handle_interrupt(int sig)
{
	t_exit *glob = &global_exit;
    if (sig == SIGINT)
	{
		ft_kill(glob);
    	write(1,"\n",1);
		// // global_exit.exit_status = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_delete_text(0, rl_end);
		if (glob->killed == 0)
        	rl_redisplay();
		glob->killed = 0;
    }
	else if (sig == SIGQUIT)
	{
        glob->exit_status = 0;
		// if (glob->killed != 0)
		// kill(glob->pid[0], SIGKILL);
    }
}

void	ft_kill(t_exit *glob)
{
	int	i;

	i = 0;
	
	while (i < glob->len)
	{
		glob->killed = 1;
		// printf("%d\n",glob->pid[i]);
		kill(glob->pid[i], SIGKILL);
		i++;
	}
	glob->len = 0;
}

void	print_cmds(char **cmds)
{
	int i = 0;
	while(cmds[i])
	{
		printf("i= %d,%s\n",i,cmds[i]);
		i++;
	}
}
int	len_cmds(char **cmds)
{
	int i = 0;
	while(cmds[i])
		i++;
	return (i);
}

int	main(int ac, char **av, char **env)
{
	t_list_env	*new_env;
	t_list_env	*m_export;
	char		*cmd ;
	char		**cmd_parsed;
	t_list		*head = NULL;
	char		*str;
	char		*trimed_str;
	t_list		*expander_list;
	t_voidlst	*commands;
	t_voidlst	*myenv;
	t_command 	*tmp;
	char 		**cmds;

	(void)ac;
	(void)av;
	new_env = get_env(env);
	m_export = env_dup(new_env);
	sort_list(m_export);
	init_glob(&global_exit);
	while (1)
	{
		signal(SIGINT, &handle_interrupt);
		signal(SIGQUIT, &handle_interrupt);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline("minishell> ");
		if (!cmd)
		{
			write(1,"exit\n",5);
			exit(global_exit.exit_status);
		}
		signal(SIGINT, &handle_interrupt);
		if (cmd != NULL && *cmd != '\0')
		{
			add_history(cmd);
		}
		
		trimed_str = ft_strtrim(cmd, " ");
		if (!give_tokens(&head, trimed_str))
		{
			// myfree_func(head, trimed_str, str);
			continue;
		}
		if (!compiler(head))
		{
			// myfree_func(head, trimed_str, str);
			continue;
		}
		// free(str);
		// free(trimed_str);
		head = esc_sp_after_spechar(head);
		myenv = take_env(env);
		expander_list = bash_expander(head, myenv);
		commands = bash_concate(expander_list);
		commands = parse_to_args(commands);
		// signal(SIGQUIT, &handle_interrupt);
		// display_args(commands);
		// display(commands);
		tmp = commands->content;
		cmds = tmp->args;
		// print_cmds(cmds);
		// if (is_builtin(cmds))
		// 	global_exit.exit_status =  builtin_functions(&new_env, &m_export, cmds);
		// else
		// 	execution();
			// execute(&new_env, cmds);
		//	pipe :
		ft_pipe(&m_export,  commands, &new_env);
		// free_big_list(commands);
		// free_all(cmds);
		printf("status = %d\n",global_exit.exit_status);
	}
	return (0);
}
