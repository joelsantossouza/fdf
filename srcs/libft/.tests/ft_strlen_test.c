/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:55:34 by joesanto          #+#    #+#             */
/*   Updated: 2025/09/26 13:14:26 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <atf-c.h>
#include <stdio.h>

#define	NELEM(tab, data_type) (sizeof(tab) / sizeof(data_type))
#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"

static int	i;

void	test(char *strs[], int size, size_t expected)
{
	size_t		output;
	char		*color;

	printf("---> test%02d (Expected=%lu)\n", i, expected);
	while (size--)
	{
		output = ft_strlen(strs[size]);
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:\t%s\t\t\t\tOutput: %lu\n", strs[size], output);
		printf("%s", RESET);

		ATF_CHECK_EQ(expected, output);
	}
	printf("\n\n");
}

// TEST 00
ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "String of size 0");
}
ATF_TC_BODY(test00, tc)
{
	char	*test00[] = {"", 0, "\0"};
	size_t	expected = 0;

	i = 0;
	test(test00, NELEM(test00, char *), expected);
}

// TEST 01
ATF_TC(test01);
ATF_TC_HEAD(test01, tc)
{
	atf_tc_set_md_var(tc, "descr", "String of size 1");
}
ATF_TC_BODY(test01, tc)
{
	char	*test01[] = {"a", "\n", "\001", "\177", "\x0a", "\200", "", "", "Z"};
	size_t	expected = 1;

	i = 1;
	test(test01, NELEM(test01, char *), expected);
}

// TEST 02
ATF_TC(test02);
ATF_TC_HEAD(test02, tc)
{
	atf_tc_set_md_var(tc, "descr", "String of size 32");
}
ATF_TC_BODY(test02, tc)
{
	char	*test02[] = {
		"W0gJvWSs0PqdrCNYo5cxIiMxd0EPXvUd",
		"qZLNW8RwHSTdjwjigW5tocnjQ28k6rS2",
		"hZ7jDCE1c82StgFLRztBGwFPeTAg48Bw",
		"QN7Umc862ZGKOSlR1HO2zbmoBpH90YeZ",
		"gKibl5vfUuwDIca8EfCJV3YQAXyL1P6t"
	};
	size_t	expected = 32;

	i = 2;
	test(test02, NELEM(test02, char *), expected);
}

// BONUS TEST
#ifdef LONG_STR
# include <string.h>
ATF_TC(test03);
ATF_TC_HEAD(test03, tc)
{
	atf_tc_set_md_var(tc, "descr", "String of long size");
}
ATF_TC_BODY(test03, tc)
{
	char	*test03[] = {
		LONG_STR
	};
	size_t	expected = strlen(LONG_STR);

	i = 3
	test(test03, NELEM(test03, char *), expected);
}
#endif

// TEST PROGRAM
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);
	ATF_TP_ADD_TC(tp, test01);
	ATF_TP_ADD_TC(tp, test02);
#ifdef LONG_STR
	ATF_TP_ADD_TC(tp, test03);
#endif

	return atf_no_error();
}
