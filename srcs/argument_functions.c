/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:16:17 by csinglet          #+#    #+#             */
/*   Updated: 2019/01/31 20:16:19 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		reset_arg_lens(void)
{
	t_node		*cur;
	int			i;

	if (ti.arg_lens != NULL)
		free(ti.arg_lens);
	if (!(ti.arg_lens = (int *)malloc(sizeof(int) * ti.ac)))
		fatal("Failed to allocate memory\n");
	cur = ti.args;
	i = -1;
	while (++i < ti.ac)
	{
		ti.arg_lens[i] = ft_strlen(cur->value);
		cur = cur->next;
	}
}

void			deselect_all_args(void)
{
	t_node		*cur;
	t_node		*first;

	cur = ti.args;
	first = ti.args;
	while (cur != NULL)
	{
		cur->is_selected = 0;
		if (cur->next == first)
			break ;
		cur = cur->next;
	}
	ti.total_selected = 0;
}

static void		delete_arg(t_node **cur)
{
	t_node		*to_delete;
	t_node		*next;
	t_node		*prev;

	to_delete = *cur;
	if (to_delete == ti.args)
	{
		if (ti.args == ti.args->next)
			ti.args = NULL;
		else
			ti.args = ti.args->next;
		*cur = to_delete->next;
	}
	else if (to_delete->next == ti.args)
		*cur = to_delete->prev;
	else
		*cur = to_delete->next;
	next = to_delete->next;
	prev = to_delete->prev;
	next->prev = prev;
	prev->next = next;
	free(to_delete);
	ti.ac--;
}

void			delete_selected_args(void)
{
	t_node		*cur;
	t_node		*next;

	cur = ti.args;
	if (ti.total_selected == 0 || ti.ac == 1)
	{
		delete_arg(&ti.cur_arg);
		reset_arg_lens();
		return ;
	}
	while (cur->next != ti.args)
	{
		next = cur->next;
		if (cur->is_selected == 1)
			delete_arg(&cur);
		cur = next;
	}
	ti.total_selected = 0;
	reset_arg_lens();
}
