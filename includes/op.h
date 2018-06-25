/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2018/06/25 23:22:17 by rbechir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include "libftprintf.h"

//# define IND_SIZE	2
//# define REG_SIZE	4
//# define DIR_SIZE	REG_SIZE

# define REG_CODE	1
# define DIR_CODE	2
# define IND_CODE	3

//# define MAX_ARGS_NUMBER	4
//# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
//# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR	'#'
# define LABEL_CHAR		':'
# define DIRECT_CHAR	'%'
# define SEPARATOR_CHAR	','

# define LABEL_CHARS	"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER	16

//# define CYCLE_TO_DIE	1536
//# define CYCLE_DELTA	50
//# define NBR_LIVE		21
//# define MAX_CHECKS		10

//typedef char	t_arg_type;

# define T_REG	1
# define T_DIR	2
# define T_IND	4
# define T_LAB	8

# define PROG_NAME_LENGTH	128
# define COMMENT_LENGTH		2048
# define HEADER_LENGTH		(PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct	s_idx
{
	int				idx;
	struct s_idx	*next;
}				t_idx;

typedef struct	s_lbl
{
	char			*name;
	int				confirmed;
	int				add;
	t_idx			*replace;
	struct s_lbl	*next;
}				t_lbl;

typedef struct	s_asm
{
	int		i;
	int		fd;
	char	*line;
	char	*r_str;
	char	*cor_file;
	char	*data;
	t_lbl	*label;
}				t_asm;

typedef struct	s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}				t_header;

void			cw_display_labels(t_asm *comp);

void			cw_get_header(t_asm *comp);
void			cw_get_instructions(t_asm *comp);
int				cw_get_label(t_asm *comp, int start);
void			cw_live(t_asm *comp, int i);
void			cw_ld(t_asm *comp, int i);
void			cw_st(t_asm *comp, int i);
void			cw_add(t_asm *comp, int i);
void			cw_sub(t_asm *comp, int i);
void			cw_and(t_asm *comp, int i);
void			cw_or(t_asm *comp, int i);
void			cw_xor(t_asm *comp, int i);
void			cw_zjmp(t_asm *comp, int i);
void			cw_ldi(t_asm *comp, int i);
void			cw_sti(t_asm *comp, int i);
void			cw_fork(t_asm *comp, int i);
void			cw_lld(t_asm *comp, int i);
void			cw_lldi(t_asm *comp, int i);
void			cw_lfork(t_asm *comp, int i);
void			cw_aff(t_asm *comp, int i);
void			cw_clean_line(t_asm *comp);
void			cw_error(t_asm *comp, char *str);
void			cw_free_struct(t_asm *comp);
void			cw_create_file(t_asm *comp);

#endif
