/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:17:57 by ysaber            #+#    #+#             */
/*   Updated: 2024/03/29 15:20:00 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = ft_malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new_str == NULL)
		return (NULL);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*sub;
	int		str_len;
	int		i;

	str_len = ft_strlen(s);
	if (start >= str_len)
		return (NULL);
	if (len > str_len - start)
		len = str_len - start;
	sub = ft_malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[len] = '\0';
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = (char *)ft_malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (s1);
	str = ft_malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str);
}

char	*ft_strjoin2(char *s1, char *s2, char *s3)
{
	char	*new_str;
	t_exe	exe;

	exe.i = 0;
	exe.j = 0;
	exe.k = 0;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	if (!s3)
		s3 = ft_strdup("");
	new_str = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1));
	if (new_str == NULL)
		return (NULL);
	while (s1[exe.i])
		new_str[exe.k++] = s1[exe.i++];
	while (s2[exe.j])
		new_str[exe.k++] = s2[exe.j++];
	exe.j = 0;
	while (s3[exe.j])
		new_str[exe.k++] = s3[exe.j++];
	new_str[exe.k] = '\0';
	return (new_str);
}

char	*ft_strtrim(char *str, char *set)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = strlen(str) - 1;
	while (str[i] && ft_strchr(set, str[i]))
		i++;
	while (j > i && ft_strchr(set, str[j]))
		j--;
	ret = ft_malloc(sizeof(char) * (j - i + 2));
	ft_strlcpy(ret, &str[i], j - i + 2);
	return (ret);
}
