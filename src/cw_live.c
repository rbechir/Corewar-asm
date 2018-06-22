/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbechir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 05:21:37 by rbechir           #+#    #+#             */
/*   Updated: 2018/06/22 07:53:05 by rbechir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	cw_check_args(t_asm *comp, int i)
{
	if (comp->line[i] != DIRECT_CHAR)
		cw_error(comp, "Bad parameter (live instruction)\n");
}

void		cw_live(t_asm *comp, int i)
{
	i = ft_skip_whitespace(comp->line, i);
	cw_check_args(comp, i);
}
