/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parc1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:22:47 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/28 11:56:33 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_single_token(t_list *tmp, t_list *hd, t_env *env, int *flag)
{
	if (tmp->type == T_HEREDOC)
	{
		if (process_heredoc_token(tmp, hd) == 1)
			return (1);
		*flag = 2;
	}
	if (*flag == 0)
		tmp->content = checking_dolar(tmp->content, env);
	tmp->content = skip_qouts(tmp->content, tmp->remove_qoute);
	if (*flag != 0)
		(*flag)--;
	return (0);
}

int	process_token_list(t_list *hd, t_env *env)
{
	t_list	*tmp;
	int		flag;

	tmp = hd;
	flag = 0;
	while (tmp)
	{
		if (handle_single_token(tmp, hd, env, &flag) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	process_heredoc_token(t_list *tmp, t_list *hd)
{
	char	*heredoc_file;

	if (tmp->next)
	{
		heredoc_file = heredoc(tmp->next->content);
		if (!heredoc_file)
		{
			cleanup_heredoc_files(hd);
			return (1);
		}
		tmp->next->content = heredoc_file;
	}
	return (0);
}
