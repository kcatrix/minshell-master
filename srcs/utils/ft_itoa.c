/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:52:04 by acolin            #+#    #+#             */
/*   Updated: 2022/02/01 12:34:20 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_size_int(long n)
{
	int	i;

	i = 1;
	if (n < 0)
		i++;
	while ((n / 10) != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_fill(int *i, char *s, long n)
{
	if (n >= 10)
	{
		ft_fill(i, s, n / 10);
		ft_fill(i, s, n % 10);
	}
	else
		s[(*i)++] = n + '0';
}

/**
 * Alloue (avec malloc(3)) et retourne une chaine de
 * caractères représentant l’integer reçu en argument.
 * Les nombres négatifs doivent être gérés.
 *
 * \param	n	l’integer à convertir.
 * \return		La chaine de caractères représentant l’integer.
 * 				NULL si l’allocation échoue.
 */
char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*s;

	nb = n;
	s = malloc(sizeof(char) * (ft_size_int(nb) + 1));
	if (!s)
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		s[i++] = '-';
		nb *= -1;
	}
	ft_fill(&i, s, nb);
	s[i] = '\0';
	return (s);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}
