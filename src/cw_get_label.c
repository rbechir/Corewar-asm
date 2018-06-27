/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_get_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbechir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 03:25:42 by rbechir           #+#    #+#             */
/*   Updated: 2018/06/27 03:05:48 by rbechir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

static void	cw_update_lbl(t_asm *comp, t_lbl **label, int conf)
{
	t_idx	*tmp;

	if (conf && !(*label)->confirmed)
	{
		(*label)->confirmed = 1;
		(*label)->add = comp->i - HEADER_LENGTH;
		free(comp->r_str);
	}
	else if (!conf && !(*label)->replace)
	{
		if (!((*label)->replace = (t_idx*)malloc(sizeof(t_idx) * 1)))
			cw_error(comp, "Malloc error (creating index structure)\n");
		(*label)->replace->idx = comp->i - HEADER_LENGTH;
		(*label)->replace->next = NULL;
	}
	else if (!conf)
	{
		tmp = (*label)->replace;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_idx*)malloc(sizeof(t_idx) * 1)))
			cw_error(comp, "Malloc error (adding index)\n");
		tmp->next->idx = comp->i - HEADER_LENGTH;
		tmp->next->next = NULL;
	}
}

static void	cw_create_lbl(t_asm *comp, t_lbl **label, int conf)
{
	if (!(*label = (t_lbl*)malloc(sizeof(t_lbl) * 1)))
		cw_error(comp, "Malloc error (creating label structure)\n");
	(*label)->confirmed = conf;
	(*label)->next = NULL;
	if (conf)
	{
		(*label)->name = comp->r_str;
		(*label)->add = comp->i - HEADER_LENGTH;
		(*label)->replace = NULL;
	}
	else
	{
		conf = 1;
		while (ft_strchr(LABEL_CHARS, comp->r_str[conf]))
			conf++;
		if (!((*label)->name = ft_strsub(comp->r_str, 1, conf - 1)))
			cw_error(comp, "Malloc error (creating label)\n");
		(*label)->add = 0;
		if (!((*label)->replace = (t_idx*)malloc(sizeof(t_idx) * 1)))
			cw_error(comp, "Malloc error (creating label structure)\n");
		(*label)->replace->idx = comp->i - HEADER_LENGTH;
		(*label)->replace->next = NULL;
	}
}

static int	cw_read_unconf_label(t_asm *comp, int start)
{
	int		ret;
	t_lbl	*tmp;
	char	*name;

	while (ft_strchr(LABEL_CHARS, comp->r_str[start]))
		start++;
	if (!comp->label)
		cw_create_lbl(comp, &comp->label, 0);
	else
	{
		if (!(name = ft_strsub(comp->r_str, 1, start - 1)))
			cw_error(comp, "Malloc error (creating label)\n");
		ret = 1;
		tmp = comp->label;
		while (tmp && (ret = ft_strcmp(tmp->name, name)) && tmp->next)
			tmp = tmp->next;
		free(name);
		if (ret)
			cw_create_lbl(comp, &tmp->next, 0);
		else
			cw_update_lbl(comp, &tmp, 0);
	}
	return (start);
}

static int	cw_read_conf_label(t_asm *comp, int start)
{
	int		ret;
	t_lbl	*tmp;

	if (!(comp->r_str = ft_strsub(comp->line, start,
		ft_strchri(comp->line, LABEL_CHAR) - start)))
		cw_error(comp, "Malloc error (creating label)\n");
	if (!comp->label)
		cw_create_lbl(comp, &comp->label, 1);
	else
	{
		ret = 1;
		tmp = comp->label;
		while (tmp && (ret = ft_strcmp(tmp->name, comp->r_str)) && tmp->next)
			tmp = tmp->next;
		if (ret)
			cw_create_lbl(comp, &tmp->next, 1);
		else
			cw_update_lbl(comp, &tmp, 1);
	}
	comp->r_str = NULL;
	return (ft_strchri(comp->line, LABEL_CHAR) + 1);
}

int			cw_get_label(t_asm *comp, int start)
{
	int		i;

	i = ft_skip_whitespace(comp->line, start);
	if (!start)
	{
		while (ft_strchr(LABEL_CHARS, comp->line[i]))
			i++;
		if (comp->line[i] != LABEL_CHAR)
			return (start);
		return (cw_read_conf_label(comp, start));
	}
	return (cw_read_unconf_label(comp, start));
}
