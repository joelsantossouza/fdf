/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrnul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:44:58 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/02 09:58:39 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstrnul(const char *haystack, const char *needle)
{
	size_t	needle_len;

	if (!haystack || !needle)
		return (0);
	if (*needle)
	{
		needle_len = ft_strlen(needle);
		while (*haystack)
			if (ft_strncmp(haystack++, needle, needle_len) == 0)
				return ((char *)(haystack - 1));
	}
	return ((char *) haystack);
}
