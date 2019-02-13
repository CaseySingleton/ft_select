/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:20:41 by csinglet          #+#    #+#             */
/*   Updated: 2019/01/21 16:20:42 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		move_horizontal(int key)
{
	if (ti.cur_arg->next == NULL)
		return ;
	if (key == LEFT_KEY || key == A_KEY)
		ti.cur_arg = ti.cur_arg->prev;
	else
		ti.cur_arg = ti.cur_arg->next;
}

static void		move_vertical(int key)
{
	int			i;

	i = -1;
	if (ti.cur_arg->next == NULL)
		return ;
	while (++i < ti.vert_index)
	{
		if (key == DOWN_KEY || key == S_KEY)
			ti.cur_arg = ti.cur_arg->next;
		else
			ti.cur_arg = ti.cur_arg->prev;
	}
}

static void		select_arg(void)
{
	ti.cur_arg->is_selected ^= 1;
	ti.total_selected += ti.cur_arg->is_selected == 1 ? 1 : -1;
	if (ti.cur_arg->next != NULL)
		ti.cur_arg = ti.cur_arg->next;
}

static void		actions(int key)
{
	if (key == ESC_KEY)
		safe_exit();
	else if (key == RIGHT_KEY || key == LEFT_KEY || key == A_KEY ||
			key == D_KEY || key == TAB_KEY)
		move_horizontal(key);
	else if (key == UP_KEY || key == DOWN_KEY || key == W_KEY || key == S_KEY)
		move_vertical(key);
	else if (key == SPACE_KEY)
		select_arg();
	else if (key == BSP_KEY || key == DEL_KEY)
		delete_selected_args();
	else if (key == R_KEY)
		deselect_all_args();
}

void			input_loop(void)
{
	long		key;

	key = 0;
	while (1)
	{
		if (ti.args == NULL)
			safe_exit();
		if (key == ENTER_KEY)
			break ;
		print_args();
		key = 0;
		read(STDERR_FILENO, &key, 8);
		actions(key);
	}
}
