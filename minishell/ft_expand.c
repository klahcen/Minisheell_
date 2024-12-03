/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:47:51 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/04 18:00:44 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_dollar(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!ft_strcmp(str, "$"))
		return (NULL);
	new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '\"')
			i++;
		new_str[j] = str[i];
		i++;
		j++;
	}
	return (new_str);
}

int	can_expand(char *str)
{
	int	i;
	int	count_dq;
	int	count_sq;

	i = 0;
	count_dq = 0;
	count_sq = 0;
	while (str[i] && str[i] != '$')
	{
		if (str[i] == '\"')
			count_dq++;
		if (str[i] == '\'')
			count_sq++;
		i++;
	}
	if (str[i] == '$')
	{
		if (is_quote(str[i + 1]) == 1)
			return (0);
		if (count_sq % 2 != 0)
			return (0);
		if (count_dq % 2 != 0 || (count_sq % 2 == 0 && count_dq % 2 == 0))
			return (1);
	}
	return (0);
}

t_exe	process_dollar(t_exe exe, char *str, t_env *envir, int *expanded)
{
	exe.s1 = ft_substr(str, 0, exe.i);
	exe.i++;
	exe.len = exe.i;
	while (str[exe.i] && (ft_isalnum(str[exe.i]) || str[exe.i] == '_'
			|| str[exe.i] == '?'))
		exe.i++;
	exe.s3 = ft_substr(str, exe.len, exe.i - exe.len);
	if (exe.s3[0] == '?')
		exe.s2 = ft_expand_hadi(exe.s3);
	else
		exe.s2 = ft_get_env_value(exe.s3, envir);
	if (exe.s2 == NULL)
		return (exe);
	exe.s1 = ft_strjoin2(exe.s1, exe.s2, &str[exe.i]);
	if (exe.s1 == NULL)
		return (exe);
	*expanded = 1;
	str = exe.s1;
	exe.i = 0;
	return (exe);
}

char	*ft_expand(char *str, t_env *envir, int *expanded)
{
	t_exe	exe;

	if (str == NULL)
		return (NULL);
	exe.i = 0;
	if (can_expand(str) == 0)
		return (str);
	else
	{
		while (str[exe.i])
		{
			if (str[exe.i] == '$')
			{
				exe = process_dollar(exe, str, envir, expanded);
				if (exe.s2 == NULL || exe.s1 == NULL)
					return (str);
				str = exe.s1;
			}
			else
				exe.i++;
		}
	}
	return (remove_all_quotes(str));
}
