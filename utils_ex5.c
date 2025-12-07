/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:58:43 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/29 13:45:15 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target_directory(t_spcmd *lst, t_env **env)
{
	char	*target;

	if (!lst->cmd[1])
	{
		target = get_env_value("HOME", *env);
		if (!target)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			check_env("?=", "1", *env);
			return (NULL);
		}
	}
	else if (lst->cmd[2] != NULL)
	{
		printf("cd: too many arguments\n");
		check_env("?=", "1", *env);
		return (NULL);
	}
	else
	{
		target = lst->cmd[1];
	}
	return (target);
}

static void	update_oldpwsd(char *path_old, t_env **env)
{
	char	*tmp;

	if (path_old)
	{
		tmp = ft_strjoin("OLDPWD=", path_old);
		if (tmp)
		{
			ft_export(tmp, env);
		}
	}
}

static int	change_directoryy(char *target, char *path_old, t_env **env)
{
	(void)path_old;
	if (chdir(target) == -1)
	{
		perror("cd");
		check_env("?=", "1", *env);
		return (1);
	}
	return (0);
}

static void	finalize_cd(char *path_old, t_env **env)
{
	char	*path_nw;

	path_nw = getcwd(NULL, 0);
	if (!path_nw)
	{
		handle_getcwd_errorrr(path_old, env);
		return ;
	}
	update_oldpwsd(path_old, env);
	update_pwd(path_nw, env);
	check_env("?=", "0", *env);
	free(path_nw);
}

void	ft_cd(t_spcmd *lst, t_env **env)
{
	char	*path_old;
	char	*target;

	path_old = getcwd(NULL, 0);
	if (!path_old)
	{
		perror("getcwd failed");
		return ;
	}
	target = get_target_directory(lst, env);
	if (!target)
	{
		free(path_old);
		return ;
	}
	if (change_directoryy(target, path_old, env))
	{
		free(path_old);
		return ;
	}
	finalize_cd(path_old, env);
	free(path_old);
}
