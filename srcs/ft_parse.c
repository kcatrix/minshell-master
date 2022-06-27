/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:19:11 by acolin            #+#    #+#             */
/*   Updated: 2022/02/02 13:13:39 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_quote(char *cmd)
{
	size_t	i;
	char	quote;

	remove_backslash(cmd);
	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '"' && cmd[i - 1] != '\\')
			|| (cmd[i] == '\'' && cmd[i - 1] != '\\'))
		{
			quote = cmd[i];
			rm_char(cmd, i++);
			while (cmd[i] != quote)
			{
				if (cmd[i] == '\\')
					i++;
				i++;
			}
			rm_char(cmd, i);
		}
		i++;
	}
}

t_cmd	*get_cmd(char *cmd)
{
	t_cmd	*cmdt;
	char	**splited;
	int		i;

	cmdt = malloc(sizeof(t_cmd));
	cmdt->cmd = cmd;
	cmdt->redirections = malloc(sizeof(t_redir *));
	cmdt->redirections[0] = get_redirection(&cmd, 0);
	splited = ft_split_mod(cmd, ' ');
	i = 0;
	while (splited[i])
		del_quote(splited[i++]);
	cmdt->kw = splited[0];
	if (splited[0])
		ft_tolower(cmdt->kw);
	else
		g_env.error = -1;
	cmdt->args = splited;
	return (cmdt);
}

t_cmd	**parse_line(char *cmd)
{
	char	**cmd_tab;
	t_cmd	**cmdt;
	size_t	i;

	cmd_tab = ft_split_mod(cmd, '|');
	i = 0;
	while (cmd_tab[i])
		i++;
	cmdt = malloc(sizeof(t_cmd *) * (i + 1));
	i = 0;
	while (cmd_tab[i])
	{
		cmdt[i] = get_cmd(cmd_tab[i]);
		i++;
	}
	free(cmd_tab);
	cmdt[i] = NULL;
	return (cmdt);
}

void	parse(char *cmd)
{
	char	**cmd_tab;
	size_t	i;

	if (!check_pip(cmd) || ft_is_open(cmd))
		return ;
	cmd_tab = ft_split_mod(cmd, ';');
	free(cmd);
	if (!cmd_tab)
		return ;
	i = 0;
	while (cmd_tab[i])
		i++;
	g_env.lines = malloc(sizeof(t_line *) * (i + 1));
	i = 0;
	while (cmd_tab[i])
	{
		g_env.lines[i] = malloc(sizeof(t_line));
		g_env.lines[i]->line = cmd_tab[i];
		g_env.lines[i]->cmds = parse_line(cmd_tab[i]);
		i++;
	}
	free(cmd_tab);
	g_env.lines[i] = NULL;
}
