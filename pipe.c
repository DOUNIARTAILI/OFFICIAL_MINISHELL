/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:42:33 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/10 23:53:38 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(char **cmds, t_list_env **new_env, t_list_env **m_export)
{
	if (is_builtin(cmds))
		global_exit.exit_status =  builtin_functions(new_env, m_export, cmds);
	else
		execute(new_env, cmds);
}

void first_command(int *fd, t_voidlst *commands, t_list_env **new_env, t_list_env **m_export)
{
	pid_t pid;
	int old_fd_in;
	int old_fd_out;
	
	if(is_builtin(((t_command *)commands->content)->args))
			global_exit.exit = 1;
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("dup2 failed");
		close(fd[1]);
		redirections(commands, ((t_command *)commands->content)->redirections, m_export, new_env);
		exit(global_exit.exit_status);
	}
	old_fd_in = fd[0];
	old_fd_out = fd[1];
	close(old_fd_out);
}

t_voidlst	*in_between_commands(t_voidlst *head_bet, int *fd, t_list_env **new_env, t_list_env **m_export)
{
	int save_fd;
	pid_t pid;

	while (head_bet->next != NULL)
	{
		if(is_builtin(((t_command *)head_bet->content)->args))
			global_exit.exit = 1;
		save_fd = fd[0]; // Save the previous read end of the pipe + Update the read end of the pipe for the next iteration
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			if (dup2(save_fd, STDIN_FILENO) == -1)
				perror("dup2 failed");
			close(save_fd);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				perror("dup2 failed");
			close(fd[1]);
			redirections(head_bet, ((t_command *)head_bet->content)->redirections, m_export, new_env);
			exit(global_exit.exit_status);
		}
		close(fd[1]);
		close(save_fd);
		head_bet = head_bet->next;
	}
	return (head_bet);
}

void last_command(int *fd, t_voidlst *commands, t_list_env **new_env, t_list_env **m_export)
{
	int old_fd_in;
	pid_t pid;

	old_fd_in = fd[0];
	if(is_builtin(((t_command *)commands->content)->args))
			global_exit.exit = 1;
	pid = fork();
	if (pid == 0)
	{
		if (dup2(old_fd_in, STDIN_FILENO) == -1)
			perror("dup2 failed");
		close(old_fd_in);
		redirections(commands, ((t_command *)commands->content)->redirections, m_export, new_env);
	}
	close(old_fd_in);	
}

void	ft_pipe(t_list_env **m_export, t_voidlst *commands, t_list_env **new_env)
{
	t_command	*mycommand;

	int fd[2];
	int len;
	
	mycommand = commands->content;
	len = list_size(commands);
	global_exit.size = len;
	if (len == 1)
		redirections(commands, mycommand->redirections, m_export, new_env);
	else if (len > 1)
	{
		pipe(fd);
		first_command(fd, commands, new_env, m_export);
		commands = commands->next;
		if (len > 2)
		{
			commands = in_between_commands(commands, fd, new_env, m_export);
		}
		last_command(fd, commands, new_env, m_export);
	}
	while (waitpid(-1, &global_exit.exit_status, 0) > 0);
	exit_status(global_exit.exit_status);
}
