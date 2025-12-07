/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex11.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:24:38 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/29 14:49:50 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_external(t_spcmd *lst, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*path_env;

	path_env = ft_getenv("PATH", env);
	if (!lst || !lst->cmd || !lst->cmd[0])
		return ;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		handle_child_process(lst, env, path_env);
	}
	else
	{
		waitpid(pid, &status, 0);
		update_exit_status(env, status);
	}
}

t_data	*set_get_data(void *p)
{
	static t_data	*ptr;

	if (p)
		ptr = p;
	return (ptr);
}

void	srch(char *str, int *i)
{
	if (!str)
	{
		return ;
	}
	while (str[*i])
	{
		if (str[*i] == '=')
			break ;
		(*i)++;
	}
}

void	update_pwd(char *path_nw, t_env **env)
{
	char	*tmp;

	if (path_nw)
	{
		tmp = ft_strjoin("PWD=", path_nw);
		if (tmp)
		{
			ft_export(tmp, env);
		}
	}
}

int	handle_getcwd_errorrr(char *path_old, t_env **env)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories:", 2);
	ft_putstr_fd(" No such file or directory\n", 2);
	check_env("?=", "1", *env);
	update_oldpwd(path_old, env);
	return (1);
}
