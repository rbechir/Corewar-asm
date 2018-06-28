/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_get_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbechir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 01:13:45 by rbechir           #+#    #+#             */
/*   Updated: 2018/06/28 20:44:33 by rbechir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static char	*cw_conv(t_asm *comp, intmax_t nbr, int size)
{
	int		neg;
	char	*str;

	neg = 0;
	if (!(str = (char*)malloc(sizeof(char) * size)))
		cw_error(comp, "Malloc error (converting number)\n");
	if (nbr < 0)
		neg = 1;
	while (--size >= 0)
	{
		if (neg && !size)
			str[size] = (nbr % 256) - 1;
		else
			str[size] = (nbr % 256);
		nbr = nbr / 256;
	}
	return (str);
}

void		cw_get_number(t_asm *comp, int start, int size)
{
	intmax_t	nbr;
	char		*tmp;

	if (!(tmp = ft_strsub(comp->r_str, start, ft_strlen(comp->r_str) - start)))
		cw_error(comp, "Malloc error (getting number)\n");
	nbr = ft_atoimax(tmp);
	free(tmp);
	tmp = cw_conv(comp, nbr, size);
	start = 0;
	while (size-- > 0)
		comp->data[comp->i++] = tmp[start++];
	free(tmp);
}
