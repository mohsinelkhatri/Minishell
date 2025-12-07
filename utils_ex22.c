/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex22.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:38:50 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/30 14:14:33 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_command_not_found(char **argv)
{
	char	*cmd_name;

	if (argv[0])
		cmd_name = ft_strdup(argv[0]);
	else
		cmd_name = NULL;
	if (cmd_name && cmd_name[0] != '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putendl_fd(": command not found", 2);
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(127);
	}
	else
	{
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(1);
	}
}

static int	child_exit(void)
{
	char	*i;
	int		j;

	i = ft_getenv("?", set_get_env(NULL));
	j = ft_atoi(i);
	free_garbage(&set_get_data(NULL)->lst_gc_env);
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	exit(j);
}

static void	execute_child_process(t_spcmd *cmd, int fd_in, int pipefd[2],
		t_env *env)
{
	char	**argv;
	char	*cmd_path;

	argv = cmd->cmd;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_fd(fd_in, pipefd, cmd);
	handle_redirections(cmd->redir);
	if (is_built_in(argv[0]))
	{
		ex_built_in(cmd, &env);
		child_exit();
	}
	cmd_path = get_cmd_path(argv[0], env);
	if (!cmd_path)
		handle_command_not_found(argv);
	execve(cmd_path, argv, reverse_env(env));
	handle_exec_error(argv[0]);
	free_garbage(&set_get_data(NULL)->lst_gc_env);
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	exit(1);
}

pid_t	fork_and_execute(t_spcmd *cmd, int fd_in, int pipefd[2], t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execute_child_process(cmd, fd_in, pipefd, env);
	}
	else
	{
		waitpid(pid, &status, 0);
		update_exit_status(env, status);
	}
	return (pid);
}
