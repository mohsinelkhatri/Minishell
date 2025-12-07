/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex21.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:13:15 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/29 15:11:49 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_fd(int fd_in, int pipefd[2], t_spcmd *cmd)
{
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

static void	ft_enoent(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" command not found\n", 2);
	free_garbage(&set_get_data(NULL)->lst_gc_env);
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	exit(127);
}

void	handle_exec_error(char *cmd_name)
{
	if (!cmd_name || cmd_name[0] == '\0')
	{
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(1);
	}
	if (errno == ENOENT)
	{
		ft_enoent(cmd_name);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd((char *)cmd_name, 2);
		ft_putendl_fd(" : Permission denied", 2);
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(126);
	}
	else
	{
		perror(cmd_name);
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(1);
	}
}

void	join_lists(t_list **a, t_list *b)
{
	t_list	*last;

	if (!*a)
	{
		*a = b;
		return ;
	}
	last = *a;
	while (last->next)
		last = last->next;
	last->next = b;
}
