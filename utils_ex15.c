/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex15.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:28:07 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/27 19:15:27 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_child_io(t_spcmd *curr, int fd_in, int pipefd[2])
{
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (curr->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	execute_command(t_spcmd *curr, t_env *env)
{
	handle_redirections(curr->redir);
	if (is_built_in(curr->cmd[0]))
		ex_built_in(curr, &env);
	else
		execute_external(curr, env);
}

void	child_process(t_spcmd *curr, int fd_in, int pipefd[2], t_env *env)
{
	setup_child_io(curr, fd_in, pipefd);
	execute_command(curr, env);
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	free_garbage(&set_get_data(NULL)->lst_gc_env);
	exit(EXIT_SUCCESS);
}

void	handle_fork_error(void)
{
	perror("fork");
	exit(EXIT_FAILURE);
}
