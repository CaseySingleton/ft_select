/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 23:05:51 by csinglet          #+#    #+#             */
/*   Updated: 2019/01/11 23:07:57 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Allowd functions:
**
** isatty, ttyname, ttyslot
** ioctl
** getenv
** tcsetattr, tcgetattr
** tgetent, getflag, tgetnum, tgetstr, tgoto, tputs
** open, close, write
** malloc, free
** read, exit
** signal
**
** type 'stty -a' in a unix terminal to get a list of signals
*/

static void		check_valid_terminal(void)
{
	int			success;
	char		buff[2048];

	ft_bzero(buff, 2048);
	if ((ti.term_name = getenv("TERM")) == NULL)
		fatal("No given name for ther terminal\n");
	if (!isatty(STDERR_FILENO))
		fatal("ft_select must be run with a proper terminal\n");
	if ((success = tgetent(buff, ti.term_name)) < 1)
	{
		if (success == 0)
			fatal("Unable to load terminal database\n");
		if (success == -1)
			fatal("No terminal entry found\n");
	}
}

static void		term_info_init(void)
{
	int			i;

	if (!(ti.arg_lens = (int *)malloc(sizeof(int *) * ti.ac)))
		fatal("Failed to allocate memory");
	i = -1;
	while (++i < ti.ac)
		ti.arg_lens[i] = ft_strlen(ti.av[i]);
	ti.args = list_init(ti.ac, ti.av);
	ti.cur_arg = ti.args;
}

/*
**	tgetstr()
**	ti - use non-canonical mode
**	vi - make cursor invisible
*/

static void		ft_select(void)
{
	check_valid_terminal();
	term_info_init();
	load_custom_config();
	signals_init();
	input_loop();
	restore_default_config();
	print_selected_args();
	free_allocated_memory();
}

int				main(int argc, char *argv[])
{
	if (argc == 1)
		ft_printf("temp text\n");
	else
	{
		ti.ac = argc - 1;
		ti.av = argv + 1;
		ft_select();
	}
	return (0);
}
