/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouad_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 23:18:12 by mouaammo          #+#    #+#             */
/*   Updated: 2023/06/10 22:59:13 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_glob(t_exit *glob)
{
	int i = -1;
	glob->killed = 0;
	glob->exit_status = 0;
	glob->exit = 0;
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
		// rl_replace_line("", 0);
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
	t_list		*expander_list;
	t_voidlst	*commands;
	t_voidlst	*myenv;
	char 		**cmds;

	(void)ac;
	(void)av;
	new_env = get_env(env);
	m_export = env_dup(new_env);
	sort_list(m_export);
	init_glob(&global_exit);
	myenv = take_env(env);
	while (1)
	{
		head = NULL;
		signal(SIGINT, &handle_interrupt);
		signal(SIGQUIT, &handle_interrupt);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline("\033[6;32mminishell>> :\033[0m");
		if (!cmd)
			exit(global_exit.exit_status);
		signal(SIGINT, &handle_interrupt);
		if (*cmd)
			add_history(cmd);
		commands = tokenizer_and_grammar(cmd, head, myenv);
		if (!commands)
			continue ;
		commands = parse_to_args(commands);
		ft_pipe(&m_export, commands, &new_env);
		free_and_reset(commands);
	}
	free_myenv(myenv);
	return (0);
}
