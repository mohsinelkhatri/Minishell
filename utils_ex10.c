/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:15:19 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/28 10:53:29 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*checking_dolar_doc(char *str, t_env *env)
{
	t_dolar	dolar;

	init_dolar(&dolar);
	while (str[dolar.i])
	{
		if (str[dolar.i] == '$')
			handle_dolar(&dolar, str, env);
		else
		{
			dolar.result = ft_strjoin(dolar.result, ft_substr(str, dolar.i, 1));
			dolar.i++;
		}
	}
	return (dolar.result);
}

void	handle_sigint_heredoc(int sig)
{
	int	fd;

	(void)sig;
	free_garbage(&set_get_data(NULL)->lst_gc_env);
	free_garbage(&set_get_data(NULL)->lst_gc_g);
	write(1, "\n", 1);
	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
	exit(130);
}

int	in_qout(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
