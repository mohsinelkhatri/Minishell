/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:47:03 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/28 09:46:05 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_pwd(t_env *env)
{
	char	*str;
	char	*pwd_env;

	str = getcwd(NULL, 0);
	if (str)
	{
		printf("%s\n", str);
		update_env("PWD", str, env);
		free(str);
	}
	else
	{
		pwd_env = get_env_value("PWD", env);
		if (pwd_env)
			printf("%s\n", pwd_env);
		else
		{
			ft_putstr_fd("pwd:error retrieving ", 2);
			ft_putstr_fd("current directory:getcwd:cannot", 2);
			ft_putstr_fd("access parent directories:", 2);
			ft_putstr_fd(":No such file or directory\n", 2);
		}
	}
	check_env("?=", "0", env);
}

static void	print_echo_args(char **args, int start_index)
{
	int	i;

	i = start_index;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	ex_echo(t_spcmd *lst, t_env *env)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (lst->cmd[1] == NULL)
	{
		printf("\n");
		check_env("?=", "0", env);
		return ;
	}
	if (ft_strcmp(lst->cmd[1], "-n") == 0)
	{
		option = 1;
		i++;
	}
	print_echo_args(lst->cmd, i);
	if (option == 0)
		printf("\n");
	check_env("?=", "0", env);
}

int	check_nber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
