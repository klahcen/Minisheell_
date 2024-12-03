/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysaber <ysaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:54:32 by ysaber            #+#    #+#             */
/*   Updated: 2024/04/04 16:55:13 by ysaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_arg_sub_part(char *arg)
{
	arg = ft_substr(arg, 0, ft_strrch(arg, '$'));
	if (arg[0] == '\0')
		arg = arg + 1;
	return (arg);
}

static char	*process_arg_sub(char *arg)
{
	int	k;

	if (arg && arg[0] != '$')
		arg = process_arg_sub_part(arg);
	if (arg && arg[0] == '$')
	{
		k = 1;
		if (ft_isdigit(arg[1]) == 1)
			arg = ft_substr(arg, 2, ft_strlen(arg));
		else
		{
			while (arg[k])
			{
				if (ft_isalpha(arg[k]) || ft_isdigit(arg[k]))
					k++;
				else
					break ;
			}
			arg = ft_substr(arg, k, ft_strlen(arg));
		}
	}
	return (arg);
}

static char	**process_arg(char **args, int i, t_env **envir, int *expanded)
{
	int		j;
	t_exe	nor;

	args[i] = ft_remove_dollar(args[i]);
	args[i] = ft_expand(args[i], *envir, expanded);
	nor.i = ft_strlen(args[i]);
	if (!(*expanded))
		args[i] = remove_all_quotes(args[i]);
	nor.j = ft_strlen(args[i]);
	if (ft_strchr(args[i], '$') && str_isnt_in_env(args[i], *envir) == 1
		&& nor.i == nor.j)
	{
		j = i;
		while (args[j])
		{
			args[j] = process_arg_sub(args[j]);
			j++;
		}
	}
	return (args);
}

char	**ft_process_args(char **args, t_env **envir)
{
	int	i;
	int	expanded;
	int	skip_next;

	i = 0;
	expanded = 0;
	skip_next = 0;
	while (args[i])
	{
		if (skip_next)
			skip_next = 0;
		else if (strcmp(args[i], "<<") == 0)
			skip_next = 1;
		else
		{
			args = process_arg(args, i, envir, &expanded);
			if (args[i] == NULL)
				break ;
		}
		i++;
	}
	return (args);
}
