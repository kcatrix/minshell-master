/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 11:21:16 by andrew            #+#    #+#             */
/*   Updated: 2022/02/01 08:54:33 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redirs(t_redir *r)
{
	t_redir	*n;

	while (r)
	{
		n = r->next;
		free(r->kw);
		free(r);
		r = n;
	}
}

void	free_lines(void)
{
	int		i;
	int		k;
	int		j;

	k = 0;
	while (g_env.lines[k])
	{
		free(g_env.lines[k]->line);
		i = 0;
		while (g_env.lines[k]->cmds[i])
		{
			free(g_env.lines[k]->cmds[i]->cmd);
			j = 0;
			while (g_env.lines[k]->cmds[i]->args[j])
				free(g_env.lines[k]->cmds[i]->args[j++]);
			free(g_env.lines[k]->cmds[i]->args);
			free_redirs(g_env.lines[k]->cmds[i]->redirections[0]);
			free(g_env.lines[k]->cmds[i]->redirections);
			free(g_env.lines[k]->cmds[i++]);
		}
		free(g_env.lines[k]->cmds);
		free(g_env.lines[k]);
		k++;
	}
	free(g_env.lines);
}

void	free_cmds(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}
