/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 11:04:49 by andrew            #+#    #+#             */
/*   Updated: 2022/02/01 14:01:09 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	putstr(int fd, char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

void	putstr_endl(int fd, char *s)
{
	putstr(fd, s);
	write(fd, "\n", 1);
}
