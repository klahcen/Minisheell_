/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkazaz <lkazaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 03:03:22 by lkazaz            #+#    #+#             */
/*   Updated: 2024/03/30 12:57:49 by lkazaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*t_getdata(t_env *envir, char *str)
{
	while (envir)
	{
		if (!ft_strcmp(envir->name, str))
			return (envir->value);
		envir = envir->next;
	}
	return (NULL);
}

void	ft_modifenv(t_env *envir, char *chr, char *new)
{
	while (envir)
	{
		if (!ft_strcmp(envir->name, chr))
			envir->value = ft_strdup(new);
		envir = envir->next;
	}
}

int	ft_pwd(void)
{
	char	s[256];

	getcwd(s, 256);
	printf("%s\n", s);
	return (0);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	return (ft_lstlast(lst->next));
}

int	ft_isalpha(int a)
{
	if ((a >= 97 && a <= 122) || (a >= 65 && a <= 90))
		return (1);
	else
		return (0);
}
