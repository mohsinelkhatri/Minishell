/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:49:31 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/26 14:17:10 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_quoted_substring(char *str, int *index, char quote_char)
{
	int	start;

	start = (*index)++;
	while (str[*index] && str[*index] != quote_char)
		(*index)++;
	if (str[*index] == quote_char)
		(*index)++;
	if (quote_char == '\'')
		return (ft_substr(str, start, *index - start));
	return (ft_substr(str, start, *index - start));
}

int	skip_single_quotes(char *str, int i)
{
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	return (i);
}

int	skip_double_quotes(char *str, int i)
{
	i++;
	while (str[i] && str[i] != '"')
		i++;
	return (i);
}

int	present_dolar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i = skip_single_quotes(str, i);
		else if (str[i] == '"')
			i = skip_double_quotes(str, i);
		else if (str[i] == '$')
		{
			if (ft_isalpha(str[i + 1]) == 1 || str[i + 1] == '_'
				|| str[i + 1] == '?')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
