/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:54:43 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/30 18:05:45 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;

	if (!s)
		return (0);
	n = ft_strnlen(s, n);
	new = (char *) malloc(sizeof(char) * (n + 1));
	if (!new)
		return (0);
	ft_strlcpy(new, s, n + 1);
	return (new);
}
