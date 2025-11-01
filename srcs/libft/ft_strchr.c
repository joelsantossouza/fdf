/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 22:31:00 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/29 09:19:36 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	find;

	find = (char) c;
	if (s)
	{
		while (*s)
			if (*s++ == find)
				return ((char *)(s - 1));
		if (find == 0)
			return ((char *) s);
	}
	return (0);
}
