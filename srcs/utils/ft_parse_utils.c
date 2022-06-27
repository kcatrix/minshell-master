/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:35:27 by lmataris          #+#    #+#             */
/*   Updated: 2022/02/02 13:12:52 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rm_space_end(char **cmds)
{
	int		i;
	size_t	j;

	i = 0;
	while (cmds[i])
	{
		j = ft_strlen(cmds[i]) - 1;
		while (cmds[i][j] == ' ' && j > 0)
		{
			rm_char(cmds[i], j);
			j -= 1;
		}
		i++;
	}
}

void	expend(char **cmd)
{
	size_t	i;
	int		exp;

	i = 0;
	exp = 1;
	while (cmd[0][i])
	{
		if (cmd[0][i] == '"' && exp == 1)
			expend_var_quote(cmd, &i, cmd[0][i]);
		if (cmd[0][i] == '\'')
			exp = 0;
		if (cmd[0][i] == '$' && exp == 1)
			expend_var(cmd, i);
		if (cmd[0][i] == '\\')
			i++;
		i++;
	}
}

int	inc_i(char *cmd, char c)
{
	int		i;
	char	quote;

	i = 0;
	while (cmd[i] && cmd[i] != c)
	{
		if ((cmd[i] == '\'' || cmd[i] == '\"'))
		{
			if (cmd[i - 1] != '\\')
			{
				quote = cmd[i];
				i++;
				while (cmd[i] && cmd[i] != quote)
				{
					if (cmd[i] == quote && cmd[i - 1] != '\\')
						break ;
					else
						i++;
				}
			}
		}
		i++;
	}
	return (i);
}

int	check_pip(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i += inc_i(cmd + i, '|');
		if (cmd[i + 1] == '|')
		{
			g_env.error = 1;
			printf("ERROR : DOUBLE PIPE\n");
			free(cmd);
			return (0);
		}
		i++;
	}
	return (1);
}

void	delete_redirection(char **cmd, char c)
{
	int		i;
	int		j;
	int		nb_char;

	i = inc_i(cmd[0], c);
	j = i;
	while ((cmd[0][j] == c || cmd[0][j] == ' ') && cmd[0][j])
		j++;
	while (cmd[0][j] != ' ' && cmd[0][j])
		j++;
	while (cmd[0][j] == ' ' && cmd[0][j])
		j++;
	nb_char = j - i;
	while (nb_char--)
	{
		j = i;
		while (cmd[0][j])
		{
			cmd[0][j] = cmd[0][j + 1];
			j++;
		}
	}
}
