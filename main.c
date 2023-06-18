/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:18:12 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/18 22:07:17 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_glob(t_exit *glob)
{
	int	i;

	i = -1;
	glob->heredoc = 0;
	glob->killed = 0;
	glob->gnl = 0;
	glob->exit_status = 0;
	glob->exit = 0;
	glob->flag = 1;
	while (++i < 1024)
		glob->pid[i] = 0;
}

void	prompt(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_interrupt(int sig)
{
	t_exit	*glob;

	glob = &g_global_exit;
	if (sig == SIGINT)
	{
		if (ft_kill(glob))
			glob->exit_status = 130;
		else
			glob->exit_status = 1;
		if (g_global_exit.heredoc)
		{
			g_global_exit.flag = 0;
			glob->exit_status = 1;
			close(0);
			g_global_exit.heredoc = 0;
		}
		else
			prompt();
		glob->killed = 0;
	}
	else if (sig == SIGQUIT)
		glob->exit_status = 0;
}

void	handler(int sig)
{
	t_exit	*glob;

	glob = &g_global_exit;
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
		g_global_exit.flag = 1;
		g_global_exit.heredoc = 0;
		rl_catch_signals = 0;
		head = NULL;
		g_global_exit.exit = 0;
		signal(SIGINT, &handle_interrupt);
		signal(SIGQUIT, &handle_interrupt);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGUSR1, &handler);
		cmd = readline("\033[6;32mminishell>> \033[0m");
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
		if (ttyname(0))
			ft_pipe(&m_export, commands, &new_env);
		else
		{
			char *tty = ttyname(1);
			int fd = open(tty, O_RDONLY);
			dup2(fd, 0);
		}
		// free_and_reset(commands);
	}
	free_myenv(new_env);
	return (0);
}
