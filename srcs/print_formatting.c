/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_formatting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 19:06:40 by csinglet          #+#    #+#             */
/*   Updated: 2019/01/13 19:06:41 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		largest_in_column(int cur, int args_per_row)
{
	int			largest;
	int			i;

	largest = 0;
	i = cur % args_per_row;
	while (i < ti.ac)
	{
		if (ti.arg_lens[i] > largest)
			largest = ti.arg_lens[i];
		i += args_per_row;
	}
	return (largest);
}

static int		get_args_per_row(void)
{
	int			args_per_row;
	int			line_space_required;
	int			i;

	args_per_row = ti.ac;
	while (args_per_row > 0)
	{
		i = -1;
		line_space_required = 0;
		while (++i < args_per_row)
		{
			line_space_required += largest_in_column(i, args_per_row) + PADDING;
			if (line_space_required >= ROWS)
				break ;
		}
		if (i == args_per_row)
			return (args_per_row);
		args_per_row--;
	}
	return (args_per_row);
}

void			print_selected_args(void)
{
	t_node		*cur;
	int			args_printed;
	int			i;

	cur = ti.args;
	args_printed = 0;
	i = -1;
	while (++i < ti.ac)
	{
		if (cur->is_selected == 1)
		{
			ft_putstr_fd(cur->value, STDOUT_FILENO);
			args_printed++;
			if (args_printed < ti.total_selected)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		cur = cur->next;
	}
}

void			print_args(void)
{
	t_node		*cur;
	int			args_per_row;
	int			padding;
	int			i;

	cur = ti.args;
	tputs(tgetstr("cl", NULL), 1, for_tputs);
	if ((args_per_row = get_args_per_row()) == 0 || ti.ac / args_per_row > COLS)
		return (window_too_small_message());
	ti.vert_index = args_per_row;
	i = -1;
	while (++i < ti.ac)
	{
		padding = largest_in_column(i % args_per_row, args_per_row) -
			ft_strlen(cur->value) + PADDING;
		print_node_fd(cur, STDERR_FILENO);
		if ((i + 1) % args_per_row == 0)
			ft_putchar_fd('\n', STDERR_FILENO);
		else if (i + 1 < ti.ac)
			ft_put_multichar_fd(padding, ' ', STDERR_FILENO);
		cur = cur->next;
	}
}
