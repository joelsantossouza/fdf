/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:53:16 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/30 13:13:11 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *) s1;
	p2 = (const unsigned char *) s2;
	if (!n || (!p1 && !p2))
		return (0);
	if (!p1)
		return (-1);
	if (!p2)
		return (1);
	while (*p1 == *p2 && n-- > 1)
	{
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}
