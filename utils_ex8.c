/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:11:23 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/28 16:23:31 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_output_redirection(t_redir *redir)
{
	int	fd;

	if (redir->type == T_GREAT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == T_DGREAT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return ;
	if (fd < 0)
	{
		perror(redir->file);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	handle_input_redirection(t_redir *redir)
{
	int	fd;

	if (redir->type != T_LESS && redir->type != T_HEREDOC)
		return ;
	fd = open(redir->file, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->file);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	handle_redirections(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == T_GREAT || redir->type == T_DGREAT)
			handle_output_redirection(redir);
		else if (redir->type == T_LESS || redir->type == T_HEREDOC)
			handle_input_redirection(redir);
		redir = redir->next;
	}
}

void	update_env(const char *key, const char *value, t_env *env)
{
	t_env	*new;

	while (env)
	{
		if (ft_strcmp(env->var, key) == 0)
		{
			env->val = ft_strdup_env(value);
			return ;
		}
		env = env->next;
	}
	new = ft_malloc(sizeof(t_env), &set_get_data(NULL)->lst_gc_env);
	new->var = ft_strdup_env(key);
	new->val = ft_strdup_env(value);
	new->next = NULL;
}
