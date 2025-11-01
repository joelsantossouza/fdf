/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mempset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:53:41 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/29 11:08:57 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_mempset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	set_chr;
	size_t			set_block;

	if (!s)
		return (0);
	ptr = (unsigned char *) s;
	set_chr = (unsigned char) c;
	set_block = (size_t) set_chr * 0x0101010101010101UL;
	while (n >= 8)
	{
		*(size_t *) ptr = set_block;
		ptr += 8;
		n -= 8;
	}
	while (n--)
		*ptr++ = set_chr;
	return ((void *) ptr);
}
