/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk_diff.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:44:58 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/02 11:33:43 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk_diff(const char *s, const char *reject)
{
	if (s && reject)
		while (*s)
			if (!ft_strchr(reject, *s++))
				return ((char *)(s - 1));
	return (0);
}
