/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:18:12 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/12 21:51:30 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_glob(t_exit *glob)
{
	int i = -1;
	glob->heredoc = 0;
	glob->killed = 0;
	glob->exit_status = 0;
	glob->exit = 0;
	while (++i < 1024)
		glob->pid[i] = 0;
}

void handle_interrupt(int sig)
{
	t_exit *glob = &g_global_exit;
    if (sig == SIGINT)
	{
		// if (!g_global_exit.heredoc)
		// {
			if (ft_kill(glob))
				glob->exit_status = 130;
			else
				glob->exit_status = 1;
			write(1,"\n",1);
			rl_replace_line("", 0);
			rl_on_new_line();
			if (glob->killed == 0)
				rl_redisplay();
			glob->killed = 0;
		// }
		// else
		// {
		// 	rl_callback_handler_remove();
		// 	g_global_exit.heredoc = 0;
		// }
    }
	else if (sig == SIGQUIT)
	{
        glob->exit_status = 0;
    }
}
void handler(int sig)
{
	t_exit *glob = &g_global_exit;
    if (sig == SIGUSR1)
	{
		glob->exit = 1;	
    }
}

int	ft_kill(t_exit *glob)
{
	int	i;

	i = 0;
	while (i < glob->len)
	{
		glob->killed = 1;
		kill(glob->pid[i], SIGKILL);
		i++;
	}
	glob->len = 0;
	if (i > 0)
		return (1);
	return (0);
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
	t_list		*expander_list;
	t_voidlst	*commands;
	t_voidlst	*myenv;
	char 		**cmds;

	(void)ac;
	(void)av;
	new_env = get_env(env);
	m_export = env_dup(new_env);
	sort_list(m_export);
	init_glob(&g_global_exit);
	while (1)
	{
		head = NULL;
		g_global_exit.exit = 0;
		signal(SIGINT, &handle_interrupt);
		signal(SIGQUIT, &handle_interrupt);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGUSR1, &handler);
		cmd = readline("\033[6;32mminishell>>: \033[0m");
		if (!cmd)
		{
			write(1,"exit\n",5);
			exit(g_global_exit.exit_status);
		}
		signal(SIGINT, &handle_interrupt);
		if (cmd != NULL && *cmd != '\0')
			add_history(cmd);
		commands = tokenizer_and_grammar(cmd, head, new_env);
		if (!commands)
			continue ;
		commands = parse_to_args(commands);
		ft_pipe(&m_export, commands, &new_env);
		// free_and_reset(commands);
		free(head);
		commands = NULL;
	}
	// free_myenv(new_env);
	return (0);
}
