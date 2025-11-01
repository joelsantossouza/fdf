/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ipow_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/10 20:49:15 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <atf-c.h>

#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"

double ipow(double base, size_t exponent) {
    // Special cases
    if (exponent == 0) {
        return 1.0;  // Any number^0 = 1
    }
    
    if (base == 0.0) {
        return 0.0;  // 0^n = 0 (for n > 0)
    }
    
    if (base == 1.0) {
        return 1.0;  // 1^n = 1
    }
    
    if (exponent == 1) {
        return base;
    }
    
    // Exponentiation by squaring - O(log n)
    double result = 1.0;
    double current_base = base;
    
    while (exponent > 0) {
        // If exponent is odd, multiply result by current_base
        if (exponent & 1) {
            result *= current_base;
        }
        // Square the base
        current_base *= current_base;
        // Divide exponent by 2
        exponent >>= 1;
    }
    
    return result;
}

int limit = 100;
void	test(double min, double max)
{
	double	output;
	double	expected;
	char	*color;
	int		rand_number;

	srand(time(0));
	rand_number = (rand() % limit) + 1;
	while (min <= max)
	{
		double attempt = rand() % rand_number;
		expected = ipow(min, attempt);
		output = ft_ipow(min, attempt);
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t%f - %f\n", min, attempt);
		printf("Expected:\t%f\n", expected);
		printf("Output:  \t%f\n", output);
		printf("%s", RESET);

		ATF_CHECK_EQ(expected, output);
		printf("----------\n");
		min += (double) (rand() % rand_number) / (rand() % rand_number) + 1;
	}
}

ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", "testing my ft_pow");
}
ATF_TC_BODY(test00, tc)
{
	test(-100, 129);
	test(0, 128);
}
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);

	return (atf_no_error());
}
