/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearray_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 19:25:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/10/03 12:21:16 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h>

#define TEST_NULL	1<<0
#define NELEM(tab) (sizeof(tab) / sizeof(t_input))
#define RED		"\e[0;31m"
#define GREEN	"\e[0;32m"
#define RESET	"\e[0m"

char	*tests_titles[] = {
	"NULL array",
	"VALID array",
	"Big input",
};

typedef struct s_input
{
	size_t	nmemb;
	size_t	size;
	void	(*fun)(void *);
}	t_input;

void	test(t_input tab[], size_t size, int flags)
{
	void				**array;
	void				**parray;
	size_t				j;
	static int			i;

	printf("<test%02d> %s\n", i, tests_titles[i]);
	while (size--)
	{
		if (flags & TEST_NULL)
			array = 0;
		else
		{
			array = malloc(sizeof(void *) * (tab[size].nmemb + 1));
			if (array)
			{
				parray = array;
				j = -1;
				while (++j < tab[size].nmemb)
				{
					*parray = malloc(tab[size].size);
					if (!*parray++)
						break ;
				}
				*parray = 0;
			}
		}
		ft_freearray(array, tab[size].fun);
	}
	i++;
}

int	main(void)
{
	printf("--- For this test please use Valgrind! ---\n\n");

	// TEST 00 --> NULL ARRAY
	t_input	test00[] = {
		{0, 0, free},
		{0, 0, free},
	};
	test(test00, NELEM(test00), TEST_NULL);

	// TEST 01 --> VALID ARRAY
	t_input	test01[] = {
		{0, 0, free},
		{10, 0, free},
		{10, 10, free},
		{0, 10, free},
		{100, 100, free},
		{1024, 1024, free},
		{2048, 2048, free},
	};
	test(test01, NELEM(test01), 0);

	// TEST 02 --> BIG INPUTS
	t_input	test02[] = {
		{4028, 4028, free},
		{6030, 6030, free},
		{5080, 10000, free},
		{10000, 10000, free},
	};
	test(test02, NELEM(test02), 0);

	return (0);
}
