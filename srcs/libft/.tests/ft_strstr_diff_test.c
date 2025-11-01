/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_diff_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 10:31:08 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/02 08:56:55 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <atf-c/tc.h>
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <string.h>
#include <atf-c.h>

#define NELEM(tab) (sizeof(tab) / sizeof(t_input))

#define RED			"\e[0;31m"
#define GREEN		"\e[0;32m"
#define RESET_COLOR	"\e[0m"
#define TEST_NULLS	1<<0

char	*tests_titles[] = {
	"Null Strings",
	"Empty Strings",
	"Big Strings",
	"String little Bigger Than String big",
};
static int	i;

typedef struct s_input
{
	const char	*big;
	const char	*little;
}	t_input;

char *strstr_diff(const char *haystack, const char *needle)
{
    const char *h;
    const char *n;
    
    // Return NULL if either parameter is NULL
    if (haystack == NULL || needle == NULL)
        return (NULL);
    
    // If needle is empty, return haystack (no characters to avoid)
    if (*needle == '\0')
        return ((char *)haystack);
    
    // Iterate through haystack
    while (*haystack)
    {
        h = haystack;
        n = needle;
        
        // Check if current position matches needle
        while (*h && *n && *h == *n)
        {
            h++;
            n++;
        }
        
        // If we matched the entire needle, skip past it
        if (*n == '\0')
        {
            haystack = h;
            continue;
        }
        
        // Found a character that doesn't start a needle match
        return ((char *)haystack);
    }
    
    // Reached end of string without finding non-needle character
    return (NULL);
}

void	test(t_input tab[], size_t size)
{
	char	*expected;
	char	*output;
	char	*color;

	printf("\n<test%02d> %s\n", i, tests_titles[i]);
	while (size--)
	{
		expected = strstr_diff(tab[size].big, tab[size].little);
		output = ft_strstr_diff(tab[size].big, tab[size].little);
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t\"%s\" - \"%s\"\n", tab[size].big, tab[size].little);
		printf("Expected:\t(%p) \"%s\"\n", expected, expected);
		printf("Output:  \t(%p) \"%s\"\n", output, output);
		printf("%s", RESET_COLOR);

		ATF_CHECK_EQ(output, expected);
		printf("----------\n");
	}
}

void	test_nulls(t_input tab[], size_t size)
{
	char	*expected;
	char	*output;
	char	*color;

	printf("\n<test%02d> %s\n", i, tests_titles[i]);
	while (size--)
	{
		expected = 0;
		output = ft_strstr_diff(tab[size].big, tab[size].little);
		color = expected == output ? GREEN : RED;

		printf("%s", color);
		printf("Input:   \t%s - %s\n", tab[size].big, tab[size].little);
		printf("Expected:\t(%p) %s\n", expected, expected);
		printf("Output:  \t(%p) %s\n", output, output);
		printf("%s", RESET_COLOR);

		ATF_CHECK_EQ(output, expected);
		printf("----------\n");
	}
}

// TEST 00 --> NULL STRINGS
ATF_TC(test00);
ATF_TC_HEAD(test00, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[0]);
}
ATF_TC_BODY(test00, tc)
{
	t_input	tab1[] = {
		{0, 0},
		{"hi", 0},
		{0, "hi"},
		{"", 0},
		{"\x01", 0},
		{"", 0},
		{"29fj20f9j2", 0},
		{0, ""},
		{"\000", 0},
		{0, 0},
		{"abc", 0},
	};

	i = 0;
	test_nulls(tab1, NELEM(tab1));
}

// TEST 01 --> EMPTY STRINGS
ATF_TC(test01);
ATF_TC_HEAD(test01, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[1]);
}
ATF_TC_BODY(test01, tc)
{
	t_input	tab[] = {
		{"", ""},
		{"abc", ""},
		{"", "abc"},
		{"", ""},
		{"", ""},
	};

	i = 1;
	test(tab, NELEM(tab));
}

// TEST 02 --> BIG STRINGS
ATF_TC(test02);
ATF_TC_HEAD(test02, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[2]);
}
ATF_TC_BODY(test02, tc)
{
	t_input	tab[] = {
		{"aaaaaaaaaaaaaaaaaa", "a"},
		{"lolololololo", "lo"},
		{"joeljoeljoeljoeljoeljoelcaralhojoeljoeljoel", "joel"},
		{"", ""},
		{"", "abc"},
		{"abc", ""},
		{"hello world", "world"},
		{"hello world", "planet"},
		{"abcdefgh", "cde"},
		{"abcdefgh", "xyz"},
		{"aaaaaa", "aaa"},
		{"aaaaaa", "aaaaaa"},
		{"abcdef", "abcdefg"},
		{"foo bar baz", "bar"},
		{"foo bar baz", "bazooka"},
		{"1234567890", "456"},
		{"1234567890", "098"},
		{"the quick brown fox", "quick"},
		{"the quick brown fox", "slow"},
		{"Lorem ipsum dolor sit amet", "ipsum"},
		{"Lorem ipsum dolor sit amet", "IPSUM"},
		{"test string", "test"},
		{"test string", "string"},
		{"test string", "strings"},
		{"needle in a haystack", "needle"},
		{"needle in a haystack", "stack"},
		{"needle in a haystack", "needles"},
		{"openai rocks", "rocks"},
		{"openai rocks", "openai"},
		{"openai rocks", "rock"},
		{"abcdefg", "fg"},
		{"abcdefg", "gh"},
		{"mississippi", "issi"},
		{"mississippi", "issis"},
		{"aaaaaaaaaa", "aaaa"},
		{"aaaaaaaaaa", "baaa"},
		{"", "nonempty"},
		{"short", "longerstring"},
		{"longerstring", "short"},
		{"abcdefghij", "a"},
		{"abcdefghij", "j"},
		{"abcdefghij", "z"},
		{"  spaced out  ", " "},
		{"tabs\tand\nnewlines", "\t"},
		{"tabs\tand\nnewlines", "\n"},
		{"tabs\tand\nnewlines", "new"},
		{"UPPERlower", "lower"},
		{"UPPERlower", "LOWER"},
		{"caseCASE", "CASE"},
		{"caseCASE", "case"},
		{"123abc456", "abc"},
		{"123abc456", "xyz"},
		{"repetition repetition", "repetition"},
		{"repetition repetition", "ition"},
		{"repetition repetition", "xyz"},
		{"pneumonoultramicroscopicsilicovolcanoconiosis", "volcano"},
		{"pneumonoultramicroscopicsilicovolcanoconiosis", "volcanic"},
		{"supercalifragilisticexpialidocious", "fragil"},
		{"supercalifragilisticexpialidocious", "fragile"},
		{"zyxwvutsrqponmlkjihgfedcba", "mlkj"},
		{"zyxwvutsrqponmlkjihgfedcba", "abcd"},
		{"edgecase", "edge"},
		{"edgecase", "case"},
		{"edgecase", "edgy"},
		{"prefixsuffix", "prefix"},
		{"prefixsuffix", "suffix"},
		{"prefixsuffix", "fixes"},
		{"middlewordhere", "word"},
		{"middlewordhere", "words"},
		{"hellothere", "hello"},
		{"hellothere", "there"},
		{"hellothere", "other"},
		{"onetwothree", "two"},
		{"onetwothree", "four"},
		{"randomchars!!??", "!!"},
		{"randomchars!!??", "??"},
		{"randomchars!!??", "!?"},
		{"000111222333", "111"},
		{"000111222333", "444"},
		{"multiline\nstring", "line"},
		{"multiline\nstring", "multiline\n"},
		{"multiline\nstring", "lines"},
		{"spaces in the middle", "in the"},
		{"spaces in the middle", "between"},
		{"boundary", "boundary"},
		{"boundary", "ound"},
		{"boundary", "bond"}
	};

	i = 2;
	test(tab, NELEM(tab));
}

// TEST 03 --> STR_LITTLE BIGGER THAN STR_BIG
ATF_TC(test03);
ATF_TC_HEAD(test03, tc)
{
	atf_tc_set_md_var(tc, "descr", tests_titles[3]);
}
ATF_TC_BODY(test03, tc)
{
	t_input	tab[] = {
		{"a", "abc"},
		{"b", "abcd"},
		{"", "x"},
		{"x", "xy"},
		{"ab", "abc"},
		{"cd", "cdef"},
		{"1", "123"},
		{"12", "1234"},
		{"", "hello"},
		{"h", "hello"},
		{"he", "hello"},
		{"hel", "hello"},
		{"abcd", "abcdef"},
		{"xyz", "xyzabc"},
		{"a", "ab"},
		{"b", "bc"},
		{"", "abc"},
		{"x", "xyz"},
		{"xy", "xyz"},
		{"", "1234"},
		{"1", "12345"},
		{"12", "123456"},
		{"abc", "abcdefg"},
		{"ab", "abcd"},
		{"a", "abcde"},
		{"", "test"},
		{"t", "test"},
		{"te", "test"},
		{"tes", "test"},
		{"tt", "test"},
		{"zz", "zzzz"},
		{"", "longerstring"},
		{"s", "longerstring"},
		{"st", "longerstring"},
		{"sho", "shortlong"},
		{"shor", "shortlong"},
		{"sho", "shortlonger"},
		{"", "nonempty"},
		{"n", "nonempty"},
		{"no", "nonempty"},
	};

	i = 3;
	test(tab, NELEM(tab));
}

// TEST PROGRAM
ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, test00);
	ATF_TP_ADD_TC(tp, test01);
	ATF_TP_ADD_TC(tp, test02);
	ATF_TP_ADD_TC(tp, test03);

	return (atf_no_error());
}
