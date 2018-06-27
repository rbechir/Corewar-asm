/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_get_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbechir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 01:13:45 by rbechir           #+#    #+#             */
/*   Updated: 2018/06/27 03:05:45 by rbechir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static char	*cw_conv(t_asm *comp, int nbr, int size)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		cw_error(comp, "Malloc error (converting number)\n");
	str[size--] = '\0';
	while (size >= 0)
	{
		str[size] = (nbr % 256) + 48;
		nbr = nbr / 256;
		size--;
	}
	return (str);
}

void		cw_get_number(t_asm *comp, int start, int size)
{
	int		nbr;
	char	*tmp;

	if (!(tmp = ft_strsub(comp->r_str, start, ft_strlen(comp->r_str) - start)))
		cw_error(comp, "Malloc error (getting number)\n");
	nbr = ft_atoi(tmp);
	free(tmp);
	tmp = cw_conv(comp, nbr, size);
	nbr = 0;
	while (tmp[nbr])
		comp->data[comp->i++] = tmp[nbr++];
	free(tmp);
}
