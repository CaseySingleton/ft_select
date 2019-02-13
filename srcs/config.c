/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:12:19 by csinglet          #+#    #+#             */
/*   Updated: 2019/01/31 20:12:20 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			load_custom_config(void)
{
	tcgetattr(STDERR_FILENO, &(ti.saved_attr));
	tcgetattr(STDERR_FILENO, &(ti.custom_attr));
	ti.custom_attr.c_lflag &= ~ICANON;
	ti.custom_attr.c_cc[VMIN] = 1;
	ti.custom_attr.c_cc[VTIME] = 0;
	tcsetattr(STDERR_FILENO, TCSANOW, &(ti.custom_attr));
	tputs(tgetstr("ti", NULL), 1, for_tputs);
	tputs(tgetstr("vi", NULL), 1, for_tputs);
}

void			restore_default_config(void)
{
	tcsetattr(STDERR_FILENO, TCSANOW, &(ti.saved_attr));
	tputs(tgetstr("te", NULL), 1, for_tputs);
	tputs(tgetstr("ve", NULL), 1, for_tputs);
}

void			safe_exit(void)
{
	restore_default_config();
	free_allocated_memory();
	exit(EXIT_SUCCESS);
}

void			fatal(char *error_message)
{
	int			msg_len;

	msg_len = ft_strlen(error_message);
	write(STDERR_FILENO, error_message, msg_len);
	restore_default_config();
	exit(EXIT_FAILURE);
}
