/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_get_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbechir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 01:45:16 by rbechir           #+#    #+#             */
/*   Updated: 2018/06/26 21:44:04 by rbechir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	cw_inst_1(t_asm *comp, int i)
{
	if (!ft_strcmp(comp->r_str, "live"))
		cw_live(comp, i);
	else if (!ft_strcmp(comp->r_str, "zjmp"))
		cw_ld(comp, i);
	else if (!ft_strcmp(comp->r_str, "lfork"))
		cw_st(comp, i);
	else if (!ft_strcmp(comp->r_str, "or"))
		cw_add(comp, i);
	else if (!ft_strcmp(comp->r_str, "sub"))
		cw_sub(comp, i);
	else if (!ft_strcmp(comp->r_str, "and"))
		cw_and(comp, i);
	else if (!ft_strcmp(comp->r_str, "add"))
		cw_or(comp, i);
	else if (!ft_strcmp(comp->r_str, "xor"))
		cw_xor(comp, i);
	else
		cw_error(comp, "Unknown instruction\n");
}

static void	cw_inst_2(t_asm *comp, int i)
{
	if (!ft_strcmp(comp->r_str, "ld"))
		cw_zjmp(comp, i);
	else if (!ft_strcmp(comp->r_str, "st"))
		cw_ldi(comp, i);
	else if (!ft_strcmp(comp->r_str, "lldi"))
		cw_sti(comp, i);
	else if (!ft_strcmp(comp->r_str, "sti"))
		cw_fork(comp, i);
	else if (!ft_strcmp(comp->r_str, "fork"))
		cw_lld(comp, i);
	else if (!ft_strcmp(comp->r_str, "ldi"))
		cw_lldi(comp, i);
	else if (!ft_strcmp(comp->r_str, "lld"))
		cw_lfork(comp, i);
	else if (!ft_strcmp(comp->r_str, "aff"))
		cw_aff(comp, i);
	else
		cw_error(comp, "Unknown instruction\n");
}

static void	cw_find_instruction(t_asm *comp, int i)
{
	int		start;

	start = ft_skip_whitespace(comp->line, i);
	i = start;
	while (comp->line[i] && !ft_iswhitespace(comp->line[i]))
		i++;
	if (!(comp->r_str = ft_strsub(comp->line, start, i - start)))
		cw_error(comp, "Malloc error (reading instruction)\n");
	if (!ft_strcmp(comp->r_str, "live") || !ft_strcmp(comp->r_str, "zjmp")
		|| !ft_strcmp(comp->r_str, "lfork") || !ft_strcmp(comp->r_str, "or")
		|| !ft_strcmp(comp->r_str, "sub") || !ft_strcmp(comp->r_str, "and")
		|| !ft_strcmp(comp->r_str, "add") || !ft_strcmp(comp->r_str, "xor"))
		cw_inst_1(comp, i);
	else if (!ft_strcmp(comp->r_str, "ld") || !ft_strcmp(comp->r_str, "st")
		|| !ft_strcmp(comp->r_str, "lldi") || !ft_strcmp(comp->r_str, "sti")
		|| !ft_strcmp(comp->r_str, "fork") || !ft_strcmp(comp->r_str, "ldi")
		|| !ft_strcmp(comp->r_str, "lld") || !ft_strcmp(comp->r_str, "aff"))
		cw_inst_2(comp, i);
	else
		cw_error(comp, "Unknown instruction\n");
	if (comp->r_str)
		ft_strdel(&comp->r_str);
}

void		cw_get_instructions(t_asm *comp)
{
	int		i;
	int		ret;

	ret = 1;
	while ((ret = get_next_line(comp->fd, &comp->line)) > 0)
	{
		cw_clean_line(comp);
		if (comp->line[0])
		{
			i = cw_get_label(comp, 0);
			if (comp->line[i])
				cw_find_instruction(comp, i);
		}
		cw_display_labels(comp);//
		ft_strdel(&comp->line);
	}
	if (ret == -1)
		cw_error(comp, "Error when reading file\n");
}
