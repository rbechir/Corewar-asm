/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_place_labels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbechir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 06:08:30 by rbechir           #+#    #+#             */
/*   Updated: 2018/06/27 08:48:01 by rbechir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	cw_place_labels(t_asm *comp)
{
	int		nbr;
	t_lbl	*tmp1;
	t_idx	*tmp2;

	tmp1 = comp->label;
	while (tmp1)
	{
		if (!tmp1->confirmed)
			cw_error(comp, "A label is not defined\n");
		tmp2 = tmp1->replace;
		while (tmp2)
		{	
			nbr = tmp1->add - tmp2->value;
			comp->r_str = ft_itoa(nbr);
			comp->i = tmp2->idx % 100000000;
			cw_get_number(comp, 0, tmp2->idx / 100000000);
			ft_strdel(&comp->r_str);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}
