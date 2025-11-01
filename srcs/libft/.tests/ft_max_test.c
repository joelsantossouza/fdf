/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/16 13:07:47 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <atf-c.h>

#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"

void	test(size_t size)
{
	ssize_t	output;
	ssize_t	expected;
	char	*color;
	ssize_t	a;
	ssize_t	b;

	srand(time(0));
	while (size--)
	{
		a = rand() % LONG_MAX;
		b = rand() % LONG_MAX;
		
		output = ft_max(a, b);
		if (a > b)
			expected = a;
		else
			expected = b;
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t%ld - %ld\n", a, b);
		printf("Expected:\t%ld\n", expected);
		printf("Output:  \t%ld\n", output);
		printf("%s", RESET);

		ATF_CHECK_EQ(expected, output);
		printf("----------\n");
	}
}

ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_max function");
}
ATF_TC_BODY(test00, tc)
{
	test(100);
}
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
