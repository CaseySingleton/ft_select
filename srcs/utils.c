/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 14:39:17 by csinglet          #+#    #+#             */
/*   Updated: 2019/01/22 14:39:18 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			free_allocated_memory(void)
{
	if (ti.args != NULL)
		free_list(&(ti.args));
	if (ti.arg_lens != NULL)
		free(ti.arg_lens);
}

int				for_tputs(int num)
{
	return (write(STDERR_FILENO, &num, 1));
}

void			ft_put_multichar_fd(int num_chars, int c, int fd)
{
	char		*str;

	if (num_chars < 1)
		return ;
	str = ft_strnew(num_chars);
	ft_memset(str, c, num_chars);
	write(fd, str, num_chars);
	free(str);
}

void			window_too_small_message(void)
{
	ft_put_multichar_fd((COLS / 2) - 2, '\n', STDERR_FILENO);
	ft_put_multichar_fd((ROWS / 2) - 8, ' ', STDERR_FILENO);
	ft_putstr_fd("Window too small\n", STDERR_FILENO);
	ft_put_multichar_fd((ROWS / 2) - 1, ' ', STDERR_FILENO);
	ft_putstr_fd("😭\n", STDERR_FILENO);
}
