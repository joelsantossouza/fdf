/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 14:13:04 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/30 13:12:18 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		find;

	p = (const unsigned char *) s;
	find = (unsigned char) c;
	if (p)
		while (n--)
			if (*p++ == find)
				return ((void *)(p - 1));
	return (0);
}
