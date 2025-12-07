/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_ma.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:56:47 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/29 14:36:03 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_shell(char **env, t_data *data)
{
	t_env	*lst;

	lst = NULL;
	data->lst_gc_env = NULL;
	data->lst_gc_g = NULL;
	set_get_data(data);
	lst = copy_env(env);
	set_get_env(lst);
	free_garbage(&data->lst_gc_g);
	return (lst);
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	process_command_line(t_env **lst, t_data *data)
{
	char	*cmd;

	data->lst_gc_g = NULL;
	set_get_data(data);
	cmd = readline("<minishell> ");
	if (!cmd)
		return (0);
	if (*cmd)
	{
		add_history(cmd);
		paring_cmd(cmd, lst);
	}
	free_garbage(&data->lst_gc_g);
	return (1);
}

void	print_error_message(const char *cmd, const char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)cmd, 2);
	ft_putendl_fd((char *)message, 2);
}
