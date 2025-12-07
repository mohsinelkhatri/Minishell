/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex17.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:15:11 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/28 16:36:02 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_directory(char *path, t_env **env)
{
	if (chdir(path) == -1)
	{
		perror("chdir");
		check_env("?=", "2", *env);
		return (1);
	}
	return (0);
}

void	update_oldpwd(char *old_path, t_env **env)
{
	char	*tmp;

	if (old_path)
	{
		tmp = ft_strjoin("OLDPWD=", old_path);
		if (tmp)
			ft_export(tmp, env);
	}
}

int	handle_getcwd_error(char *old_path, t_env **env)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot ", 2);
	ft_putstr_fd("access parent directories: No such file or directory\n", 2);
	check_env("?=", "1", *env);
	update_oldpwd(old_path, env);
	return (1);
}
