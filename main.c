/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:08:36 by aoussama          #+#    #+#             */
/*   Updated: 2025/08/29 14:48:10 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*set_get_env(t_env *p)
{
	static t_env	*ptr;

	if (p)
		ptr = p;
	return (ptr);
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	check_env("?=", "130", set_get_env(NULL));
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_env	*lst;

	(void)ac;
	(void)av;
	lst = init_shell(env, &data);
	while (1)
	{
		setup_signals();
		if (!process_command_line(&lst, &data))
			break ;
	}
	ft_exit(NULL, lst);
}
