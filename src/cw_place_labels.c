/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_place_labels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbechir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 06:08:30 by rbechir           #+#    #+#             */
/*   Updated: 2018/06/27 06:42:42 by rbechir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	cw_place_labels(t_asm *comp)
{
	int		nbr;
	t_lbl	*tmp;

	tmp = comp->label;
	while (tmp)
	{
		if (!tmp->confirmed)
			cw_error(comp, "A label is not defined\n");
		nbr = tmp->add - tmp->replace->value;
		comp->r_str = ft_itoa(nbr);
		comp->i = tmp->replace->idx;
		cw_get_number(comp, 0, 4);//modifier size 4
		ft_printf("%d\n", nbr);
		tmp = tmp->next;
	}
}
