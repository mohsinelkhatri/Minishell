/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ftexit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoussama <aoussama@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:09:44 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/30 10:29:14 by aoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	get_last_exit_status(t_env *env)
{
	char	*str;

	str = ft_getenv("?", env);
	if (!str)
		return (0);
	return (ft_atoi(str));
}

static long long	parse_exit_value(char *arg)
{
	char		*endptr;
	long long	val;

	errno = 0;
	val = strtoll(arg, &endptr, 10);
	if (*endptr != '\0' || errno == ERANGE || !is_numeric(arg))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (2);
	}
	return (val);
}

static void	cleanup_and_exit(int code)
{
	free_garbage(&(set_get_data(NULL)->lst_gc_env));
	free_garbage(&(set_get_data(NULL)->lst_gc_g));
	exit(code);
}

void	ft_exit(char **cmd, t_env *env)
{
	long long	exit_val;
	int			exit_code;

	ft_putstr_fd("exit\n", 2);
	if (cmd == NULL || cmd[1] == NULL)
	{
		exit_val = get_last_exit_status(env);
	}
	else if (cmd[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit_val = 1;
	}
	else
	{
		exit_val = parse_exit_value(cmd[1]);
	}
	exit_code = (int)(exit_val % 256);
	if (exit_code < 0)
		exit_code += 256;
	cleanup_and_exit(exit_code);
}
