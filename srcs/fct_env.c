/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:39:08 by acolin            #+#    #+#             */
/*   Updated: 2022/02/02 13:28:08 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_unset(t_cmd *cmd)
{
	int		i;
	size_t	size;

	if (get_var_env(cmd->args[1]))
	{
		i = 0;
		size = ft_strlen(cmd->args[1]);
		while (ft_strncmp(cmd->args[1], g_env.var_env[i], size) != 0)
			i++;
		if (g_env.var_env[i])
			free(g_env.var_env[i]);
		while (g_env.var_env[i])
		{
			g_env.var_env[i] = g_env.var_env[i + 1];
			i++;
		}
		g_env.size_env -= 1;
		g_env.status = 0;
	}
}

void	cmd_env(int fd)
{
	int	i;
	int	j;

	i = -1;
	while (g_env.var_env[++i])
	{
		j = 0;
		while (g_env.var_env[i][j])
		{
			if (g_env.var_env[i][j] == '=')
			{
				putstr_endl(fd, g_env.var_env[i]);
				break ;
			}
			j++;
		}		
	}
	g_env.status = 0;
}

int	is_ok(t_cmd *cmd, int j)
{
	if (!ft_isok(cmd->args[j]))
	{
		printf("%s: '%s': not a valid identifier\n", cmd->kw, cmd->args[j]);
		g_env.status = 1;
		return (0);
	}
	return (1);
}

void	cmd_export(int fd, t_cmd *cmd)
{
	size_t	i;
	size_t	j;

	if (cmd->args[1] == NULL)
		aff_export(fd);
	else
	{
		j = 1;
		while (cmd->args[j])
		{
			i = 0;
			while (cmd->args[j][i] && cmd->args[j][i] != '=')
				i++;
			if (!is_ok(cmd, j))
				return ;
			if (cmd->args[j][i] == '\0' && get_var_env(cmd->args[j]) == NULL)
				add_var_env(ft_strdup(cmd->args[j]), NULL);
			else if (cmd->args[j][i] != '\0')
				add_var_env(get_char(cmd->args[j], 0, i),
					ft_strdup(cmd->args[j] + i + 1));
			j++;
		}
		g_env.status = 0;
	}
}
