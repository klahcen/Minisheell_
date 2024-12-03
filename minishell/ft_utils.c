/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:21:57 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/01 05:20:23 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

t_env	*ft_create_env(char *name, char *value)
{
	t_env	*env;

	env = (t_env *)ft_malloc(sizeof(t_env));
	env->name = name;
	env->value = value;
	env->next = NULL;
	return (env);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;
	t_list	*new_node;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	if (ptr)
	{
		new_node = malloc(sizeof(t_list));
		if (new_node)
		{
			new_node->ptr = ptr;
			new_node->next = g_all.g_alloc;
			g_all.g_alloc = new_node;
		}
		else
		{
			free(ptr);
			ptr = NULL;
		}
	}
	return (ptr);
}

void	ft_free_all(t_env *envir)
{
	t_list	*tmp;

	if (envir == NULL)
	{
		free(envir);
	}
	while (g_all.g_alloc)
	{
		free(g_all.g_alloc->ptr);
		tmp = g_all.g_alloc;
		g_all.g_alloc = g_all.g_alloc->next;
		free(tmp);
	}
}
