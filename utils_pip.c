/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:51:14 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/30 13:32:26 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	*init_pipeline(t_spcmd *list, int *cmd_count, int *fd_in)
{
	*cmd_count = count_spcmd_nodes(list);
	*fd_in = 0;
	return (ft_malloc(sizeof(pid_t) * (*cmd_count),
			&set_get_data(NULL)->lst_gc_g));
}

static void	execute_all_commands(t_spcmd *list, t_env *env, pid_t *pids,
		int cmd_count)
{
	t_spcmd	*curr;
	int		fd_in;
	int		pipefd[2];
	int		i;
	pid_t	pid;

	(void)cmd_count;
	curr = list;
	fd_in = 0;
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (curr)
	{
		create_pipe_if_needed(curr, pipefd);
		pid = fork_and_execute(curr, fd_in, pipefd, env);
		pids[i++] = pid;
		close_fds_parent(&fd_in, pipefd, curr);
		curr = curr->next;
	}
}

static void	wait_children(pid_t *pids, int cmd_count)
{
	wait_for_children(pids, cmd_count);
}

void	execute_pipeline(t_spcmd *list, t_env *env)
{
	int		cmd_count;
	pid_t	*pids;

	pids = init_pipeline(list, &cmd_count, &(int){0});
	execute_all_commands(list, env, pids, cmd_count);
	wait_children(pids, cmd_count);
}
