/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:55:39 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/11 02:04:22 by mouaammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_status(int status)
{
	int	exit_status;
	if (g_global_exit.exit == 1)
	{
		g_global_exit.exit = 0;
		return;
	}
	if (status == 1 || status == 127)
		return ;
	if (WIFEXITED(status)) 
	{
		exit_status = WEXITSTATUS(status);
    }
	else if (WIFSIGNALED(status))
	{
		if (status == 2)
		{
			// ft_printf("^C\n");
			g_global_exit.exit_status = 130;
			// ft_kill(g_global_exit);
			return;
		}
		else if (status == 3)
		{
			ft_printf("Quit: 3\n");
			g_global_exit.exit_status = 131;
			return;
		}
	}
	// return (exit_status);
	g_global_exit.exit_status = exit_status;
}

int	check_slash(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return -1;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

void	ft_free(char **ret, int k)
{
	int	j;

	j = 0;
	while (j < k)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
}

char	**env_arr(t_list_env **envr)
{
	t_list_env *env;
	char		**arr;
	char		*tmp;
	int			i;
	int			len;

	i = 0;
	env = *envr;
	len = env_size(*envr);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	while (env != NULL)
	{
		tmp = ft_strjoin(env->data.key, "=");
		arr[i] = ft_strjoin(tmp, env->data.value);
		if (!arr[i])
		{
			ft_free(arr, i);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	execute(t_list_env **new_env, char **cmd_parsed)
{
	char	*pathname;
	char	**value;
	int		status;
	int		id;
	int		i;

	if (!cmd_parsed || !cmd_parsed[0])
		return ;
	if (g_global_exit.size == 1)
		id = fork();
	else
		id = 0;
	i = 0;
	int j = 0;
	if (id == 0)
	{
		g_global_exit.killed = 2;
		signal(SIGQUIT, SIG_DFL);
		if (!check_slash(cmd_parsed[0]))
		{
			if (!access(cmd_parsed[0], F_OK) && !access(cmd_parsed[0], X_OK))
				execve(cmd_parsed[0], cmd_parsed, env_arr(new_env));
			else
			{
				printf("minishell : %s: Permission denied\n", cmd_parsed[0]);
				g_global_exit.exit_status = 126;
			}
		}
		else
		{
			value = get_path_value(new_env);
			while (value[i] != NULL)
			{
				pathname = ft_strjoin(value[i], "/");
				pathname = ft_strjoin(pathname, cmd_parsed[0]);
				if (!access(pathname, F_OK) && access(pathname, X_OK))
				{
					printf("minishell: %s: Permission denied\n", pathname);
					g_global_exit.exit_status = 126;
					return;
				}
				else
					execve(pathname, cmd_parsed, env_arr(new_env));
				i++;
			}
			if (access(cmd_parsed[0], F_OK))
			{
				// stat check if directory appear this error in dislay : "bash: ./test: is a directory"
				printf("minishell: %s: command not found\n", cmd_parsed[0]);
				g_global_exit.exit_status = 127;
				// exit(g_global_exit.exit_status);
			}
		}
		exit(g_global_exit.exit_status);
		// perror("bash: ./test:  ");
	}
	// printf("status:%d\n",g_global_exit.exit);
	waitpid(-1, &status, 0);
	exit_status(status);
	// printf("status=%d, exit_status_glob=%d\n",status, g_global_exit.exit_status);
	// return (exit_status(status));
}
