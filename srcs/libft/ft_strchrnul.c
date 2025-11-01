/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:19:52 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/30 20:39:12 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchrnul(const char *s, int c)
{
	char	find;

	find = (char) c;
	if (s)
		while (*s)
			if (*s++ == find)
				return ((char *)(s - 1));
	return ((char *) s);
}
