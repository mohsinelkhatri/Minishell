/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:20:50 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/25 12:23:04 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pos(char *str, int *i)
{
	char	c;

	if (str[*i] == '\'' || str[*i] == '"')
	{
		c = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != c)
			(*i)++;
		if (str[*i] == c)
			(*i)++;
	}
	else
	{
		while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != ' '
			&& is_meta(str[*i]) == 0)
			(*i)++;
	}
}

t_list	*split_cmd(char *str, int flag)
{
	int		i;
	t_list	*head;

	i = 0;
	head = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		skip_whitespace(str, &i);
		if (str[i] == '\0')
			break ;
		if (is_meta(str[i]))
		{
			if (handle_meta_token(str, &i, &head) == 1)
				return (NULL);
		}
		else
		{
			if (handle_word_token(str, &i, &head, flag) == 1)
				return (NULL);
		}
	}
	return (head);
}

void	paring_cmd(char *cmd, t_env **env)
{
	t_list	*args;
	t_list	*hd;

	args = split_cmd(cmd, 0);
	if (args == NULL)
		return ;
	if (checking_cmd(&args, env) == 1)
		return ;
	hd = convert_dolar2(&args, *env);
	if (process_token_list(hd, *env) == 1)
		return ;
	parc_token(hd, env);
	cleanup_heredoc_files(hd);
}
