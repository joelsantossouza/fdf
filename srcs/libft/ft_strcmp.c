/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 08:40:10 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/26 10:07:26 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *) s1;
	p2 = (const unsigned char *) s2;
	if (!p1 && !p2)
		return (0);
	if (!p1)
		return (-1);
	if (!p2)
		return (1);
	while (*p1 == *p2 && *p1)
	{
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}
