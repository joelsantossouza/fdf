/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 10:07:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/08 12:04:14 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;

	psrc = (const unsigned char *) src;
	if (src)
	{
		if (dst && size)
		{
			pdst = (unsigned char *) dst;
			while (size-- > 1 && *psrc)
				*pdst++ = *psrc++;
			*pdst = 0;
		}
		while (*psrc)
			psrc++;
	}
	return ((const char *) psrc - src);
}
