/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 23:09:42 by csinglet          #+#    #+#             */
/*   Updated: 2019/01/11 23:09:43 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <sys/ioctl.h>

# include "libft.h"
# include "ft_printf.h"

# define TAB_KEY	9
# define ENTER_KEY	10
# define ESC_KEY	27
# define SPACE_KEY	32
# define STAR_KEY	42
# define A_KEY		97
# define D_KEY		100
# define R_KEY		114
# define S_KEY		115
# define W_KEY		119
# define BSP_KEY	127
# define UP_KEY		4283163
# define DOWN_KEY	4348699
# define LEFT_KEY	4479771
# define RIGHT_KEY	4414235
# define DEL_KEY	2117294875L

# define COLS (tgetnum("li"))
# define ROWS (tgetnum("co"))

# define PADDING 3

typedef struct		s_node
{
	char			*value;
	int				is_selected;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct		s_term_info
{
	char			**av;
	int				ac;
	int				*arg_lens;
	int				total_selected;
	int				vert_index;
	char			*term_name;
	struct termios	saved_attr;
	struct termios	custom_attr;
	struct s_node	*args;
	struct s_node	*cur_arg;
}					t_term_info;

struct s_term_info	ti;

/*
**	input_commands.c
*/

void				input_loop();

/*
**	signals.c
*/

void				signals_init();
void				handle_signals(int sig);

/*
**	print_formatting.c
*/

void				print_selected_args();
void				print_args();

/*
**	list_functions.c
*/

t_node				*new_node(char *value);
void				print_node_fd(t_node *node, int fd);
t_node				*list_init(int ac, char **av);
void				free_list(t_node **list);

/*
**	argument_funcitons.c
*/

void				deselect_all_args(void);
void				delete_selected_args(void);

/*
**	config.c
*/

void				load_custom_config(void);
void				restore_default_config(void);
void				safe_exit(void);
void				fatal(char *error_message);

/*
**	utils.c
*/

void				free_allocated_memory(void);
int					for_tputs(int num);
void				ft_put_multichar_fd(int num_chars, int c, int fd);
void				window_too_small_message(void);

#endif
