/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 10:43:37 by csinglet          #+#    #+#             */
/*   Updated: 2018/04/18 10:43:38 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int		i;

	i = -1;
	while (src[++i] != '\0')
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
