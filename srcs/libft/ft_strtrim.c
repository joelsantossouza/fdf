/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:03:22 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/04 18:48:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	s1 = ft_strpbrknul_diff(s1, set);
	return (ft_strndup(s1, ft_strrpbrkend_diff(s1, set) - s1 + 1));
}
