/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:42:33 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/01 11:01:05 by drtaili          ###   ########.fr       */
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
void	execute_pipe(t_list_env **new_env, char **cmd_parsed)
{
	char	*pathname;
	char	**value;
	int		id;
	int		i;

	i = 0;
	value = get_path_value(new_env);
	while (value[i] != NULL)
	{
		pathname = ft_strjoin(value[i], "/");
		pathname = ft_strjoin(pathname, cmd_parsed[0]);
		execve(pathname, cmd_parsed, NULL);
		i++;
	}
}

void	execute_commands(char *av, t_list_env **new_env)
{
	char **cmd_parsed;

	cmd_parsed = ft_split(av, ' ');
	execute_pipe(new_env, cmd_parsed);
}

void	ft_pipe(t_list_env **m_export, int *fd, int ac, char **av, t_list_env **new_env)
{
	char **cmd_parsed;
	pid_t pid;
	int old_fd_in;
	int old_fd_out;
	int save_fd;
	int i=1;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("dup2 failed");
		close(fd[1]);
		execute_commands(av[i], new_env);
		exit(0);
	}
	old_fd_in = fd[0];
	old_fd_out = fd[1];
	close(old_fd_out);
	i = 2;
	while (i < ac - 1)
	{
		save_fd = old_fd_in; // Save the previous read end of the pipe
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
			execute_commands(av[i], new_env);
			exit(0);
		}
		close(fd[1]);
		close(save_fd);
		old_fd_in = fd[0]; // Update the read end of the pipe for the next iteration
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		if (dup2(old_fd_in, STDIN_FILENO) == -1)
			perror("dup2 failed");
		close(old_fd_in);
		execute_commands(av[ac - 1], new_env);
	}
	close(old_fd_in);
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
