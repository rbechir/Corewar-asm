/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_get_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbechir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 03:25:42 by rbechir           #+#    #+#             */
/*   Updated: 2018/06/22 07:52:59 by rbechir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	cw_create_lbl(t_asm *comp, t_lbl **label, char **name)
{
	if (!(*label = (t_lbl*)malloc(sizeof(t_lbl) * 1)))
		cw_error(comp, "Malloc error (creating label structure)\n");
	(*label)->name = *name;
	(*label)->confirmed = 1;
	(*label)->add = comp->i; //a verifier
	(*label)->replace = NULL;
	(*label)->next = NULL;
}

static int	cw_read_label(t_asm *comp, int start)
{
	int		ret;
	t_lbl	*tmp;
	char	*name;

	if (!(name = ft_strsub(comp->line, start,
		ft_strchri(comp->line, LABEL_CHAR) - start)))
		cw_error(comp, "Malloc error (creating label)\n");
	if (!comp->label)
		cw_create_lbl(comp, &comp->label, &name);
	else
	{
		tmp = comp->label;
		while (tmp->next && (ret = ft_strcmp(tmp->name, name)))
			tmp = tmp->next;
		if (ret)
			cw_create_lbl(comp, &tmp->next, &name);
	}
	return (ft_strchri(comp->line, LABEL_CHAR) + 1);
}

int			cw_get_label(t_asm *comp, int start)
{
	int		i;

	i = ft_skip_whitespace(comp->line, start);
	while (ft_strchr(LABEL_CHARS, comp->line[i]))
		i++;
	if (comp->line[i] != LABEL_CHAR)
		return (start);
	return (cw_read_label(comp, start));
}
