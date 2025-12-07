/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 11:48:49 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/26 14:21:39 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_built_in(t_spcmd *lst, t_env **env)
{
	if (ft_strcmp(lst->cmd[0], "echo") == 0)
		ex_echo(lst, *env);
	else if (ft_strcmp(lst->cmd[0], "cd") == 0)
		ft_cd(lst, env);
	else if (ft_strcmp(lst->cmd[0], "pwd") == 0)
		printf_pwd(*env);
	else if (ft_strcmp(lst->cmd[0], "export") == 0)
		ft_export_hp(lst, env);
	else if (ft_strcmp(lst->cmd[0], "unset") == 0)
		ft_unset(lst, env);
	else if (ft_strcmp(lst->cmd[0], "env") == 0)
		print_env(*env);
	else if (ft_strcmp(lst->cmd[0], "exit") == 0)
		ft_exit(lst->cmd, *env);
	return (0);
}

int	env_len(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	*str_join_var_val(t_env *env)
{
	char	*tmp;

	tmp = ft_strjoin(env->var, env->val);
	return (tmp);
}

char	**env_to_array(t_env *env)
{
	int		len;
	char	**envp;
	int		i;

	len = env_len(env);
	envp = ft_malloc(sizeof(char *) * (len + 1), &set_get_data(NULL)->lst_gc_g);
	i = 0;
	while (env)
	{
		envp[i] = str_join_var_val(env);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
