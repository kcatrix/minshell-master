/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:45:14 by acolin            #+#    #+#             */
/*   Updated: 2022/02/02 13:39:48 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*set_value(char *kw, char *value)
{
	char	*str;
	char	*tmp;

	if (!value)
		return (kw);
	tmp = ft_strjoin(kw, "=");
	str = ft_strjoin(tmp, value);
	free(tmp);
	free(kw);
	free(value);
	return (str);
}

int	add_var_env(char *kw, char *value)
{
	char	**var;
	int		i;

	if (get_var_env(kw))
		return (set_var_env(kw, value));
	g_env.size_env += 1;
	var = malloc(sizeof(char *) * (g_env.size_env + 1));
	i = 0;
	while (g_env.var_env[i])
	{
		var[i] = g_env.var_env[i];
		i++;
	}
	var[i] = set_value(kw, value);
	var[++i] = NULL;
	free(g_env.var_env);
	g_env.var_env = var;
	return (1);
}

int	set_var_env(char *kw, char *value)
{
	int		i;
	size_t	j;

	i = 0;
	while (g_env.var_env[i])
	{
		j = 0;
		while (g_env.var_env[i][j] != '=' && g_env.var_env[i][j] != '\0')
			j++;
		if (ft_strncmp(g_env.var_env[i], kw, ft_strlen(kw)) == 0
			&& ft_strlen(kw) == j)
		{
			free(g_env.var_env[i]);
			g_env.var_env[i] = set_value(kw, value);
			return (1);
		}
		i++;
	}
	if (kw)
		free(kw);
	if (value)
		free(value);
	return (0);
}

char	*get_var_env(char *kw)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (g_env.var_env[i])
	{
		j = 0;
		while (g_env.var_env[i][j] != '=' && g_env.var_env[i][j] != '\0')
			j++;
		if (ft_strncmp(g_env.var_env[i], kw, ft_strlen(kw)) == 0
			&& ft_strlen(kw) == j)
			return (g_env.var_env[i] + j + 1);
		i++;
	}
	return (NULL);
}

void	init(char **ev)
{
	int		i;

	g_env.fork = 0;
	g_env.error = 0;
	set_signal(0);
	signal(SIGINT, interrupt_signal);
	signal(SIGQUIT, quit_signal);
	signal(11, quit_signal);
	i = 0;
	while (ev[i])
		i++;
	g_env.var_env = malloc(sizeof(char *) * (i + 1));
	g_env.size_env = i;
	i = -1;
	while (ev[++i])
		g_env.var_env[i] = ft_strdup(ev[i]);
	g_env.var_env[i] = NULL;
}
