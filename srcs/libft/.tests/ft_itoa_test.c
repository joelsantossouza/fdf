/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/06 21:06:46 by joesanto         ###   ########.fr       */
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

void	test(ssize_t min, ssize_t max)
{
	char	*output;
	char	*color;

	while (min <= max)
	{
		output = ft_itoa(min);
		color = min == atoi(output) ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t%ld\n", min);
		printf("Expected:\t%ld\n", min);
		printf("Output:  \t%s\n", output);
		printf("%s", RESET);

		ATF_CHECK(min == atoi(output));
		printf("----------\n");

		free(output);

		min++;
	}
}

ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "ft_itoa");
}
ATF_TC_BODY(test00, tc)
{
	test(-39830, 12090);
	test(-2147483648, -2147483647);
}
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
