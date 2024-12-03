/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:21:17 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/03 01:13:32 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_last_world(char *str)
{
	int		i;
	int		j;
	char	*last_word;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '/')
			j = i;
		i++;
	}
	if (j != 0)
		last_word = ft_substr(str, j + 1, i - j);
	else
		last_word = ft_substr(str, j, i - j);
	return (last_word);
}

static int	ft_count_words2(char *str, char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(s, str[i]))
			count++;
		i++;
	}
	return (count + 1);
}

static void	process_str(char *str, char *s, char **ret, t_exe *exe)
{
	if (ft_strchr(s, str[exe->i]))
	{
		if (exe->i != exe->k)
		{
			ret[exe->j] = ft_malloc(sizeof(char) * (exe->i - exe->k + 1));
			ft_strlcpy(ret[exe->j], &str[exe->k], exe->i - exe->k + 1);
			exe->j++;
		}
		while (ft_strchr(s, str[exe->i]) && str[exe->i])
			exe->i++;
		exe->k = exe->i;
	}
	else if (str[exe->i] == '\"' || str[exe->i] == '\'')
	{
		exe->i++;
		while (str[exe->i] != '\"' && str[exe->i] != '\'' && str[exe->i])
			exe->i++;
		if (str[exe->i] == '\"' || str[exe->i] == '\'')
			exe->i++;
	}
	else
		exe->i++;
}

char	**ft_split2(char *str, char *s)
{
	char	**ret;
	t_exe	exe;

	exe.i = 0;
	exe.j = 0;
	exe.k = 0;
	ret = ft_malloc(sizeof(char *) * (ft_count_words2(str, s) + 1));
	while (str[exe.i])
	{
		process_str(str, s, ret, &exe);
	}
	if (exe.i != exe.k)
	{
		ret[exe.j] = ft_malloc(sizeof(char) * (exe.i - exe.k + 1));
		ft_strlcpy(ret[exe.j], &str[exe.k], exe.i - exe.k + 1);
		exe.j++;
	}
	ret[exe.j] = NULL;
	return (ret);
}
