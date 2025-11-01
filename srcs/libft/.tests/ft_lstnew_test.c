/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/07 01:52:57 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <atf-c.h>

#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"
#define NELEM(tab) (sizeof(tab) / sizeof(void *))

void	test(void *tab[], size_t size)
{
	t_list	*output;
	char	*color;

	while (size--)
	{
		output = ft_lstnew(tab[size]);
		color = output->content == tab[size] && !output->next ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t%p\n", tab[size]);
		printf("Expected:\t%p - (nil)\n", tab[size]);
		printf("Output:  \t%p - %p\n", output->content, output->next);
		printf("%s", RESET);

		ATF_CHECK(output->content == tab[size] && !output->next);
		printf("----------\n");

		free(output);
	}
}

ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing some inputs in creation of a node of a linked list");
}
ATF_TC_BODY(test00, tc)
{
	char	*str = "This is a test";
	int		nbr = 42;
	char	chr = 'Z';
	t_list	*node = ft_lstnew(str);

	void	*tab[] = {
		0,
		str,
		&nbr,
		&chr,
		node,
	};

	test(tab, NELEM(tab));
}
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
