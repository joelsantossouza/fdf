/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:08:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/29 10:52:57 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;

	if (dest <= src)
		return (ft_memcpy(dest, src, n));
	if (!dest || !src)
		return (0);
	pdest = (unsigned char *) dest;
	psrc = (const unsigned char *) src;
	while (n >= 8)
	{
		n -= 8;
		*(size_t *)(pdest + n) = *(size_t *)(psrc + n);
	}
	while (n--)
		pdest[n] = psrc[n];
	return (dest);
}
