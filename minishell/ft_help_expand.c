/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 00:15:48 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/02 04:39:18 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_after_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] == '$')
		i++;
	return (&str[i]);
}

int	str_isnt_in_env(char *str, t_env *envir)
{
	int		i;
	int		j;
	char	*tmp;
	char	*new;

	new = ft_after_dollar(str);
	i = 0;
	j = 0;
	if (!ft_strcmp(new, "?"))
		return (0);
	while (envir)
	{
		tmp = envir->name;
		while (tmp[i] && new[j] && tmp[i] == new[j])
		{
			i++;
			j++;
		}
		if (tmp[i] == '\0' && (new[j] == '=' || new[j] == '\0'))
			return (0);
		i = 0;
		j = 0;
		envir = envir->next;
	}
	return (1);
}
