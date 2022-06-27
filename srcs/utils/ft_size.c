/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 19:10:37 by acolin            #+#    #+#             */
/*   Updated: 2022/01/29 19:15:50 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_size(char *kw, char *value)
{
	size_t	size;

	size = 0;
	if (value != NULL)
		size += 1;
	size += ft_strlen(kw);
	size += ft_strlen(value);
	return (size + 1);
}
