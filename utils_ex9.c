/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:13:21 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/30 13:32:55 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe_if_needed(t_spcmd *curr, int pipefd[2])
{
	if (curr->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		return (1);
	}
	else
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
		return (0);
	}
}

void	close_fds_parent(int *fd_in, int pipefd[2], t_spcmd *curr)
{
	if (*fd_in != 0)
		close(*fd_in);
	if (curr->next)
		close(pipefd[1]);
	if (curr->next)
		*fd_in = pipefd[0];
	else
		*fd_in = 0;
}

void	wait_for_children(pid_t *pids, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
}
