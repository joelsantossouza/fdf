/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:25:38 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/29 22:11:54 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (big && little)
	{
		if (!*little)
			return ((char *) big);
		little_len = ft_strlen(little);
		while (len-- >= little_len && *big)
			if (ft_strncmp(big++, little, little_len) == 0)
				return ((char *)(big - 1));
	}
	return (0);
}
