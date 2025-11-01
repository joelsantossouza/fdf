/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:08:34 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/30 18:41:48 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_min(int n1, int n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	return (ft_strndup(s + ft_min(start, ft_strlen(s)), len));
}
