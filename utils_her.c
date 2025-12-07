/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_her.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:17:05 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/28 13:31:10 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(const char *line, const char *delimiter)
{
	int	len_delim;
	int	len_line;

	len_delim = strlen(delimiter);
	len_line = strlen(line);
	if (len_line != len_delim)
		return (0);
	return (strncmp(line, delimiter, len_delim) == 0);
}

char	*open_rd_file(void)
{
	char	*str;
	int		i;
	int		fd;
	char	*file;

	str = "heredoc";
	i = 0;
	while (1)
	{
		file = ft_strjoin(ft_itoa(i), str);
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			if (errno == ENOENT)
				break ;
			else
			{
				i++;
				continue ;
			}
		}
		close(fd);
		i++;
	}
	return (file);
}

char	*read_line_or_delimiter(char *delimiter)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		ft_putstr_fd("1 delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
		return (NULL);
	}
	if (is_delimiter(line, delimiter))
	{
		return (NULL);
	}
	return (line);
}

void	parc_token(t_list *list, t_env **env)
{
	t_list	*tmp;
	t_spcmd	*result;
	t_spcmd	*cmd;

	tmp = list;
	result = NULL;
	while (tmp)
	{
		cmd = parse_command_segment(&tmp);
		if (cmd == NULL)
			return ;
		spcmd_lstadd_back(&result, cmd);
		if (tmp && tmp->type == T_PIPE)
			tmp = tmp->next;
	}
	ft_exuction(result, env);
}
