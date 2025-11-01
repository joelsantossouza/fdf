/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:34:29 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/30 18:09:33 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	i;

	if (!s || !f)
		return (0);
	new = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new)
		return (0);
	i = -1;
	while (s[++i])
		new[i] = f(i, s[i]);
	new[i] = 0;
	return (new);
}
