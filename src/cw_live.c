/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbechir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 05:21:37 by rbechir           #+#    #+#             */
/*   Updated: 2018/06/25 23:22:14 by rbechir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	cw_check_args(t_asm *comp, int i)
{
	if (comp->line[i] != DIRECT_CHAR)
		cw_error(comp, "Bad parameter (live instruction)\n");
	comp->r_str = ft_strsub(comp->line, i + 1, ft_strlen(comp->line) - i);
	i = 0;
	if (comp->r_str[i] == LABEL_CHAR)
	{
		i = cw_get_label(comp, 1);
		if (comp->r_str[i])
			cw_error(comp, "Bad parameter (live instruction)\n");	
	}
	else
	{
		if (comp->r_str[i] == 'r')
			i++;
		while (ft_isdigit(comp->r_str[i]))
			i++;
		if (comp->r_str[i])
			cw_error(comp, "Bad parameter (live instruction)\n");		
	}
}

void		cw_live(t_asm *comp, int i)
{
	ft_strdel(&comp->r_str);
	i = ft_skip_whitespace(comp->line, i);
	cw_check_args(comp, i);
}
