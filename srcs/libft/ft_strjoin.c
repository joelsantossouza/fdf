/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:54:34 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/08 13:27:54 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*pjoin;

	if (!s1 && !s2)
		return (0);
	join = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (0);
	pjoin = join;
	if (s1)
		pjoin = ft_stpcpy(pjoin, s1);
	if (s2)
		pjoin = ft_stpcpy(pjoin, s2);
	return (join);
}
