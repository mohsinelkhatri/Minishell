/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:50:52 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/30 13:32:52 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, s3);
	return (res);
}

void	update_exit_status(t_env *env, int status)
{
	char	*exit_code;

	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
		}
		else
		{
			ft_putstr_fd("\n", 2);
		}
		status = 128 + WTERMSIG(status);
	}
	else
		status = 1;
	exit_code = ft_itoa(status);
	check_env("?=", exit_code, env);
}

void	print_command_error(const char *cmd, char *path_env)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			print_error_message(cmd, ": Permission denied");
		else
			print_error_message(cmd, ": No such file or directory");
	}
	else if (!path_env || path_env[0] == '\0')
	{
		print_error_message(cmd, ": No such file or directory");
	}
	else
	{
		print_error_message(cmd, ": command not found");
	}
}

int	check_sudo(const char *cmd)
{
	if (ft_strcmp(cmd, "sudo") == 0)
	{
		ft_putstr_fd("minishell: sudo: Permission denied\n", 2);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		exit(126);
	}
	return (0);
}

int	is_slash(const char *path)
{
	int	len;

	if (!path)
		return (0);
	len = strlen(path);
	if (len == 0 || path[len - 1] == '/')
		return (0);
	return (1);
}
