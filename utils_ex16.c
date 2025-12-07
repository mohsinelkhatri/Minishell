/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:09:37 by melkhatr          #+#    #+#             */
/*   Updated: 2025/08/30 13:01:53 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sudo_case(const char *cmd, char *cmd_path)
{
	(void)cmd_path;
	if (check_sudo(cmd))
	{
		free_garbage(&set_get_data(NULL)->lst_gc_env);
		free_garbage(&set_get_data(NULL)->lst_gc_g);
		exit(126);
	}
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*get_without_trailing_slash(const char *str)
{
	int		len;
	int		new_len;
	char	*result;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_len = len;
	if (len > 0 && str[len - 1] == '/')
		new_len = len - 1;
	result = ft_malloc(new_len + 1, &set_get_data(NULL)->lst_gc_g);
	if (!result)
		return (NULL);
	ft_strncpy(result, str, new_len);
	result[new_len] = '\0';
	return (result);
}
