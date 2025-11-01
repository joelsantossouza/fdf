/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stpcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:40:10 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/08 11:52:20 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_stpcpy(char *dst, const char *src)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;

	if (!dst || !src)
		return (0);
	pdst = (unsigned char *) dst;
	psrc = (const unsigned char *) src;
	while (*psrc)
		*pdst++ = *psrc++;
	*pdst = 0;
	return ((char *) pdst);
}
