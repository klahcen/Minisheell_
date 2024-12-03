/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:54:43 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/04 17:07:03 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	return_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*tab;
	long	new;

	new = n;
	len = return_len(new);
	tab = ft_malloc(sizeof(char) * (len + 1));
	if (tab != NULL)
	{
		tab[len--] = '\0';
		if (new == 0)
			tab[0] = 48;
		if (new < 0)
		{
			tab[0] = '-';
			new *= -1;
		}
		while (new)
		{
			tab[len--] = new % 10 + 48;
			new /= 10;
		}
	}
	return (tab);
}

char	*ft_expand_hadi(char *str)
{
	char	*value;
	char	*tmp;
	char	*new;
	int		i;

	value = ft_itoa(g_all.status);
	i = 0;
	while (str[i] == '?')
		i++;
	tmp = ft_substr(str, i, ft_strlen(str));
	new = ft_strjoin2(value, tmp, NULL);
	return (new);
}
