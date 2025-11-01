/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:09:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/10 16:56:20 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <atf-c.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define RED			"\e[0;31m"
#define GREEN		"\e[0;32m"
#define RESET_COLOR	"\e[0m"

void	test(ssize_t min, ssize_t max)
{
	char	*output_dst;
	char	*color;
	size_t	len;
	int		file;
	char	template[] = "/home/joel/coding/exercises/libft/.tests/XXXXXX";

	file = mkstemp(template);
	if (file < 0)
		return ;
	printf("\n<test ft_putnbr_fd>\n");
	while (min <= max)
	{
		len = ft_digit_count(min, 10) + (min < 0);
		output_dst = malloc(len + 1);
		if (!output_dst)
			continue ;
		ft_putnbr_fd(min, file);
		lseek(file, -len, SEEK_CUR);
		read(file, output_dst, len);
		output_dst[len] = 0;

		color = atoi(output_dst) == min ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t%ld\n", min);
		printf("Expected:\t%ld\n", min);
		printf("Output:  \t%.*s\n", (int) len, output_dst);
		printf("%s", RESET_COLOR);
		
		ATF_CHECK(atoi(output_dst) == min);
		printf("----------\n");

		free(output_dst);
		min++;
	}
	unlink(template);
}
ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "Testing ft_putnbr_fd writing in files the numbers");
}
ATF_TC_BODY(test00, tc)
{
	test(-49797, 2224);
	test(-2147483648, -2147483647);
	test(2147483646, 2147483647);
}

// TEST PROGRAM
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
