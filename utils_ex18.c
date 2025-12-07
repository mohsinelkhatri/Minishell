/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex18.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 11:49:01 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/30 14:19:46 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cmd_not_found(const char *cmd, char *path_env,
		char *cmd_path)
{
	char	*helper;

	if (!cmd_path)
	{
		if (is_slash(cmd) == 0)
		{
			helper = get_without_trailing_slash(cmd);
			if (access(helper, F_OK) == 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd((char *)cmd, 2);
				ft_putstr_fd(": Not a directory", 2);
				free_garbage(&set_get_data(NULL)->lst_gc_env);
				free_garbage(&set_get_data(NULL)->lst_gc_g);
				exit(126);
			}
		}
		print_command_error(cmd, path_env);
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(127);
	}
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (1);
	}
	return (0);
}

static void	handle_permission_check(const char *cmd, char *cmd_path)
{
	if (is_directory(cmd_path))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(126);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(126);
	}
}

static void	cleanup_and_exit_failure(char *cmd_path)
{
	(void)cmd_path;
	perror("minishell");
	free_garbage(&set_get_data(NULL)->lst_gc_env);
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	exit(1);
}

void	handle_child_process(t_spcmd *lst, t_env *env, char *path_env)
{
	char	*cmd_path;
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (lst->cmd[0] == NULL || lst->cmd[0][0] == '\0')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(127);
	}
	cmd_path = get_cmd_path(lst->cmd[0], env);
	handle_sudo_case(lst->cmd[0], cmd_path);
	handle_cmd_not_found(lst->cmd[0], path_env, cmd_path);
	handle_permission_check(lst->cmd[0], cmd_path);
	envp = env_to_array(env);
	execve(cmd_path, lst->cmd, envp);
	cleanup_and_exit_failure(cmd_path);
}
