/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/13 14:23:30 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <atf-c.h>

#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"

void	test(ssize_t min, ssize_t max)
{
	size_t	output;
	size_t	expected;
	char	*color;

	while (min <= max)
	{
		expected = llabs(min);
		output = ft_abs(min);
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t%ld\n", min);
		printf("Expected:\t%ld\n", expected);
		printf("Output:  \t%ld\n", output);
		printf("%s", RESET);

		ATF_CHECK_EQ(expected, output);
		printf("----------\n");
		min++;
	}
}

ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "Recreating the ctype library");
}
ATF_TC_BODY(test00, tc)
{
	test(-123424252983, -1123424252980);
	test(-1000, 129);
	test(0, 128);
}
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
