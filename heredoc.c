/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:33:22 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/29 14:37:15 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(int fd, char *line, int flag)
{
	char	*helper;

	if (flag == 0)
	{
		helper = checking_dolar_doc(line, set_get_env(NULL));
		write(fd, helper, ft_strlen(helper));
	}
	else
	{
		write(fd, line, ft_strlen(line));
	}
	write(fd, "\n", 1);
}

static void	child_heredoc_loop(int fd, char *delimiter, int flag)
{
	char	*line;

	while (1)
	{
		line = read_line_or_delimiter(delimiter);
		if (!line)
		{
			break ;
		}
		process_line(fd, line, flag);
		free(line);
	}
}

static void	heredoc_child(char *file, char *delimiter, int flag)
{
	int	fd;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(1);
	}
	child_heredoc_loop(fd, delimiter, flag);
	close(fd);
	free_garbage(&set_get_data(NULL)->lst_gc_env);
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	exit(0);
}

static char	*heredoc_parent(pid_t pid, char *file)
{
	int	wstatus;
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &wstatus, 0);
	status = WEXITSTATUS(wstatus);
	if (status == 130 || status == 1)
	{
		if (status == 130)
			check_env("?=", "130", set_get_env(NULL));
		else
			check_env("?=", "1", set_get_env(NULL));
		unlink(file);
		return (NULL);
	}
	check_env("?=", "0", set_get_env(NULL));
	return (file);
}

char	*heredoc(char *str)
{
	pid_t	pid;
	char	*file;
	int		flag;
	char	*delimiter;

	file = open_rd_file();
	delimiter = skip_qouts(str, 0);
	flag = in_qout(str);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (NULL);
	}
	if (pid == 0)
		heredoc_child(file, delimiter, flag);
	else
		return (heredoc_parent(pid, file));
	return (file);
}
