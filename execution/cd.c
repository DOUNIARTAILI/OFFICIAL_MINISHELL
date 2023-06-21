/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drtaili <drtaili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:32:29 by drtaili           #+#    #+#             */
/*   Updated: 2023/06/21 16:32:23 by drtaili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_get_back_again(t_list_env **env)
{
	if (chdir(get_value_of_key(env, "OLDPWD")) == -1)
	{
		perror("minishell");
	}
	else
	{
		if (look_for_key("PWD", env) || look_for_key("OLDPWD", env))
			build_new_oldpwd_pwd(env);
		else
		{
			set_value_of_key(env, "OLDPWD",
				ft_strdup(get_value_of_key(env, "PWD")));
			set_value_of_key(env, "PWD",
				ft_strdup(get_value_of_key(env, "OLDPWD")));
		}
		return (0);
	}
	return (1);
}

int	ft_cd_to_home(t_list_env **env)
{
	if (chdir(get_value_of_key(env, "HOME")) == -1)
	{
		perror("minishell");
	}
	else
	{
		if (look_for_key("PWD", env) || look_for_key("OLDPWD", env))
			build_new_oldpwd_pwd(env);
		else
		{
			set_value_of_key(env, "OLDPWD",
				ft_strdup(get_value_of_key(env, "PWD")));
			set_value_of_key(env, "PWD",
				ft_strdup(get_value_of_key(env, "HOME")));
		}
		return (0);
	}
	return (1);
}

int	cd_to_relative_path(t_list_env **env, char **cmd)
{
	char	*new_path;
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("minishell");
	new_path = ft_strjoin("/", cmd[1]);
	new_path = ft_strjoin(cwd, new_path);
	if (chdir(new_path) == -1)
		perror("minishell");
	else
	{
		if (look_for_key("PWD", env) || look_for_key("OLDPWD", env))
			build_new_oldpwd_pwd(env);
		else
		{
			set_value_of_key(env, "OLDPWD",
				ft_strdup(get_value_of_key(env, "PWD")));
			set_value_of_key(env, "PWD", ft_strdup(new_path));
		}
		return (0);
	}
	return (1);
}

int	cd_to_absolute_path(t_list_env **env, char **cmd)
{
	if (chdir(cmd[1]) == -1)
		perror("minishell");
	else
	{
		if (look_for_key("PWD", env) || look_for_key("OLDPWD", env))
			build_new_oldpwd_pwd(env);
		else
		{
			set_value_of_key(env, "OLDPWD",
				ft_strdup(get_value_of_key(env, "PWD")));
			set_value_of_key(env, "PWD", ft_strdup(cmd[1]));
		}
		return (0);
	}
	return (1);
}

int	ft_cd(t_list_env **env, char **cmd)
{
	char	cwd[1024];

	if (!cmd[1])
		return (cd_only(env));
	else if (!ft_strcmp(cmd[1], "-") || !ft_strcmp(cmd[1], "~"))
	{
		if (!ft_strcmp(cmd[1], "~"))
			return (ft_cd_to_home(env));
		return (ft_cd_get_back_again(env));
	}
	else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			printf("minishell: cd: error retrieving current directory:\
			getcwd: cannot access parent directories: \
			No such file or directory\n");
			return (ft_cd_to_home(env));
		}
		else if (cmd[1][0] == '/')
			return (cd_to_absolute_path(env, cmd));
		else
			return (cd_to_relative_path(env, cmd));
	}
	return (0);
}
