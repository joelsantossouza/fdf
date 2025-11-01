/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/28 20:14:46 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <atf-c.h>

#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"

void	test(int min, int max)
{
	int		output;
	int		expected;
	char	*color;

	while (min <= max)
	{
		expected = islower(min) != 0;
		output = ft_islower(min) != 0;
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t%c\n", min);
		printf("Expected:\t%d\n", expected);
		printf("Output:  \t%d\n", output);
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
	test(-100, 10000);
}
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
