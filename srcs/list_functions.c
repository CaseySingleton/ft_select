/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:44:58 by csinglet          #+#    #+#             */
/*   Updated: 2019/01/17 18:44:59 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_node			*new_node(char *value)
{
	t_node		*new_node;

	if (!(new_node = (t_node *)malloc(sizeof(t_node))))
		fatal("Failed to allocate memory");
	ft_bzero(new_node, sizeof(t_node));
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

static void		push(t_node **list, t_node *addition)
{
	t_node		*first;
	t_node		*last;

	first = *list;
	if (first == NULL && (*list = addition) != NULL)
	{
		addition->next = addition;
		addition->prev = addition;
	}
	else if ((last = first->prev) == NULL)
	{
		last = addition;
		last->next = first;
		first->next = last;
		last->prev = first;
		first->prev = last;
	}
	else
	{
		last->next = addition;
		addition->next = first;
		first->prev = addition;
		addition->prev = last;
	}
}

void			print_node_fd(t_node *node, int fd)
{
	t_node		*cur;

	cur = node;
	if (cur == NULL)
		return ;
	if (cur->is_selected == 1)
		ft_putstr_fd("\033[7m", fd);
	if (node == ti.cur_arg)
		ft_putstr_fd(ULINE, fd);
	ft_putstr_fd(cur->value, fd);
	ft_putstr_fd(RESET, fd);
}

t_node			*list_init(int ac, char **av)
{
	t_node		*list;
	int			i;

	list = NULL;
	i = -1;
	while (++i < ac)
		push(&list, new_node(av[i]));
	return (list);
}

void			free_list(t_node **list)
{
	t_node		*next;
	t_node		*cur;

	if (*list == NULL)
		return ;
	cur = *list;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
		if (cur == *list)
			break ;
	}
}
