/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:42:33 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/08 05:17:22 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_pipe()
// {
// 	int i = 0;
// 	char *tab[] = {"uno", "dos", "tres"};
// 	int fd[2];
// 	pipe(fd);
// 	pid_t pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(fd[1], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		char *argv[] = {(char *)"sort", NULL};
// 		if (execve("/usr/bin/sort", argv, NULL) < 0)
// 			perror("can't execute");
// 	}
// 	close(fd[0]);
// 	while (i < 3)
// 	{
// 		dprintf(fd[1], "%s\n", tab[i]);
// 		i++;
// 	}
// 	close(fd[1]);
// 	int status;
// 	pid_t wpid = waitpid(pid, &status, 0);
// 	return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
// }

// func {
// 	for cmd in cmd_list:
// 		if cmd->next != NULL:
// 			int fd[2]; pipe(fd);
// 			cmd->fdout = fd[0];
// 			cmd->next->fdin = fd[1];
// 		if builtin:
// 			run_builtin(cmd)
// 		else
// 			execute(cmd)
// }

// tryyyyyy
// void	execute_pipe(t_list_env **new_env, char **cmd_parsed)
// {
// 	char	*pathname;
// 	char	**value;
// 	int		id;
// 	int		i;

// 	i = 0;
// 	value = get_path_value(new_env);
// 	while (value[i] != NULL)
// 	{
// 		pathname = ft_strjoin(value[i], "/");
// 		pathname = ft_strjoin(pathname, cmd_parsed[0]);
// 		execve(pathname, cmd_parsed, NULL);
// 		i++;
// 	}
// }

void	execute_commands(char **cmds, t_list_env **new_env, t_list_env **m_export)
{
	if (is_builtin(cmds))
		global_exit.exit_status =  builtin_functions(new_env, m_export, cmds);
	else
		execute(new_env, cmds);
}

void first_command(int *fd, char **args, t_list_env **new_env, t_list_env **m_export)
{
	pid_t pid;
	int old_fd_in;
	int old_fd_out;

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("dup2 failed");
		close(fd[1]);
		execute_commands(args, new_env, m_export);
		exit(0);
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
		save_fd = fd[0]; // Save the previous read end of the pipe // Update the read end of the pipe for the next iteration
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
			execute_commands(((t_command *)(t_voidlst *)head_bet->content)->args, new_env, m_export);
			exit(0);
		}
		close(fd[1]);
		close(save_fd);
		head_bet = head_bet->next;
	}
	return (head_bet);
}

void last_command(int *fd, char **args, t_list_env **new_env, t_list_env **m_export)
{
	int old_fd_in;
	pid_t pid;

	old_fd_in = fd[0];
	pid = fork();
	if (pid == 0)
	{
		if (dup2(old_fd_in, STDIN_FILENO) == -1)
			perror("dup2 failed");
		close(old_fd_in);
		execute_commands(args, new_env, m_export);
	}
	close(old_fd_in);	
}

void	ft_pipe(t_list_env **m_export, t_voidlst *commands, t_list_env **new_env)
{
	// pid_t pid;
	// int old_fd_in;
	// int old_fd_out;
	// int save_fd;
	int fd[2];
	int len;
	
	t_voidlst *tmp_com;
	tmp_com = commands;
	len = list_size(commands);
	global_exit.size = len;
	if (len == 1)
		execute_commands(((t_command *)(t_voidlst *)tmp_com->content)->args, new_env, m_export);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	close(fd[0]);
	// 	if (dup2(fd[1], STDOUT_FILENO) == -1)
	// 		perror("dup2 failed");
	// 	close(fd[1]);
	// 	execute_commands(((t_command *)(t_voidlst *)tmp_com->content)->args, new_env, m_export);
	// 	exit(0);
	// }
	// old_fd_in = fd[0];
	// old_fd_out = fd[1
	// close(old_fd_out);
	else if (len > 1)
	{
		pipe(fd);
		first_command(fd, ((t_command *)(t_voidlst *)tmp_com->content)->args, new_env, m_export);
		tmp_com = tmp_com->next;
		if (len > 2)
		{
			tmp_com = in_between_commands(tmp_com, fd, new_env, m_export);
		}
		last_command(fd, ((t_command *)(t_voidlst *)tmp_com->content)->args, new_env, m_export);
	}
	// while (tmp_com->next != NULL)
	// {
	// 	save_fd = old_fd_in; // Save the previous read end of the pipe
	// 	pipe(fd);
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		close(fd[0]);
	// 		if (dup2(save_fd, STDIN_FILENO) == -1)
	// 			perror("dup2 failed");
	// 		close(save_fd);
	// 		if (dup2(fd[1], STDOUT_FILENO) == -1)
	// 			perror("dup2 failed");
	// 		close(fd[1]);
	// 		execute_commands(((t_command *)(t_voidlst *)tmp_com->content)->args, new_env, m_export);
	// 		exit(0);
	// 	}
	// 	close(fd[1]);
	// 	close(save_fd);
	// 	old_fd_in = fd[0]; // Update the read end of the pipe for the next iteration
	// 	tmp_com = tmp_com->next;
	// }
	// pid = fork();
	// if (pid == 0)
	// {
	// 	if (dup2(old_fd_in, STDIN_FILENO) == -1)
	// 		perror("dup2 failed");
	// 	close(old_fd_in);
	// 	execute_commands(((t_command *)(t_voidlst *)tmp_com->content)->args, new_env, m_export);
	// }
	// close(old_fd_in);
	while (waitpid(-1, &global_exit.exit_status, 0) > 0);
	exit_status(global_exit.exit_status);
}

// ./minishell < nn.txt sort > out.txt
// 0			1 2		 3	  4	5		| ac = 6 | ac - 2 = 4

// void	redirections(int ac, char **av)
// {
// 	int red_input;
// 	int red_output;
// 	int app_output;

// 	red_input = av[1];
// 	red_output = 0;
// 	app_output = 0;
// 	int i = 1;
// 	while (i < ac)
// 	{
// 		// Input Redirection
// 		if (red_input == '<')
// 		{
// 			int fd_in = open(av[2], O_RDONLY, 0644);//av[2] howa input file mnin anqraw
// 			if (fd_in == -1)
// 			{
// 				perror("Failed to open input file");
// 				return;
//         	}
// 			dup2(fd_in, 0);
// 			close(fd_in);
// 		}
// 		// Output Redirection
// 		else if (av[ac - 2] == '>')
// 		{
// 			int fd_out = open(av[ac - 2], O_WRONLY | O_CREAT | O_TRUNC, 0666); // 0666 the 0 means that this is in octal
// 			if (fd_out == -1)
// 			{
// 				perror("Failed to open input file");
// 				return;
//         	}
// 			dup2(fd_out, 1);
// 			close(fd_out);
// 		}
// 		else if (av[ac - 2] == '>>')
// 		{
// 			int d_fd_out = open(av[ac - 2], O_WRONLY | O_CREAT |  O_APPEND, 0666);
// 			if (d_fd_out == -1)
// 			{
// 				perror("Failed to open input file");
// 				return;
//         	}
// 			dup2(d_fd_out, 1);
// 			close(d_fd_out);
// 		}
// 		// Execute the command now
// 	}
// }
