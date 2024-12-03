/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exc1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 12:11:03 by lkazaz            #+#    #+#             */
/*   Updated: 2024/04/01 05:24:17 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strrch(char *str, char c)
{
	int	len;

	len = ft_strlen(str);
	while (len > 0)
	{
		if (str[len] == c)
			return (len);
		len--;
	}
	return (0);
}

char	*ft_substrr(char *str, int i)
{
	char	*retl;
	int		len;
	int		j;

	len = 0;
	j = 0;
	len = ft_strlen(str);
	retl = ft_malloc((len - i + 1) * sizeof(char));
	if (!retl)
		return (NULL);
	while (i < len)
	{
		retl[j] = str[i];
		i++;
		j++;
	}
	retl[j] = '\0';
	return (retl);
}

char	**ft_next_env(t_env *envir, char **env)
{
	int	i;

	i = 0;
	while (envir)
	{
		env[i] = ft_strdup(envir->name);
		if (envir->value)
			env[i] = ft_strjoin(env[i], "=");
		env[i] = ft_strjoin(env[i], envir->value);
		envir = envir->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	**ft_env(t_env *envir)
{
	char	**env;
	t_env	*tmp;
	int		size;
	int		i;

	tmp = envir;
	size = 0;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	env = ft_malloc((size + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	tmp = envir;
	while (tmp)
	{
		env[i] = ft_malloc(ft_strlen(tmp->name) + ft_strlen(tmp->value) + 1);
		if (!env[i++])
			return (NULL);
		tmp = tmp->next;
	}
	return (ft_next_env(envir, env));
}

t_redirect	*ft_lstl(t_redirect *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (ft_lstl(lst->next));
}
