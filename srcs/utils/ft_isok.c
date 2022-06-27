/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:58:31 by acolin            #+#    #+#             */
/*   Updated: 2022/02/02 13:06:11 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_num(char *str)
{
	int		i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (1);
	return (0);
}

int	ft_isok(char *str)
{
	int	l;
	int	i;

	l = 0;
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalpha(str[i]))
		{
			l = 1;
			i++;
		}
		else if (ft_isdigit(str[i]) && l == 1)
			i++;
		else
			return (0);
	}
	if (i == 0)
		return (0);
	return (1);
}

int	ft_is_alphanum(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i] || ft_isalnum(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_is_open(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			ignore_quote(str, &i, str[i]);
		if (str[i] == '\0')
		{
			g_env.error = 1;
			printf("ERROR : quote unclosed\n");
			free(str);
			return (1);
		}
		i++;
	}
	return (0);
}
