/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_udigit_count_test.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/11 09:39:07 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>
#include <atf-c.h>

#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"

size_t udigit_count(size_t value, unsigned int base) {
    if (base < 2) return 0; // invalid base

    size_t count = 1; // at least one digit (for 0)
    while (value >= base) {
        value /= base;
        count++;
    }
    return count;
}

void	test(ssize_t min, ssize_t max)
{
	size_t	output;
	size_t	expected;
	char	*color;
	int		base;

	while (min <= max)
	{
		base = -1;
		while (++base <= 16)
		{
			expected = udigit_count(min, base);
			output = ft_udigit_count(min, base);
			color = expected == output ? GREEN : RED;

			printf("%s", color);
			printf("Input:   \t%ld - %d\n", min, base);
			printf("Expected:\t%lu\n", expected);
			printf("Output:  \t%lu\n", output);
			printf("%s", RESET);

			ATF_CHECK_EQ(expected, output);
			printf("----------\n");
		}
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
	test(-3983, 12090);
	test(39830342424, 39830342425);
	test(-39830342425, -39830342424);
}
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
