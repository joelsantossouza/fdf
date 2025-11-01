/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrpbrkend_diff.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 18:04:02 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/09 18:27:06 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrpbrkend_diff(const char *s, const char *reject)
{
	const char	*ptr;

	if (!s || !reject)
		return (0);
	ptr = s;
	while (*s)
		if (!ft_strchr(reject, *s++))
			ptr = (s - 1);
	return ((char *) ptr);
}
