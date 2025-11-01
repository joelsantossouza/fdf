/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:42:40 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/02 15:45:53 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_word_count(char const *s, char c)
{
	size_t	nwords;

	if (!s)
		return (0);
	nwords = 0;
	while (*s)
	{
		s = ft_strchrnul_diff(s, c);
		nwords += *s != 0;
		s = ft_strchrnul(s, c);
	}
	return (nwords);
}
