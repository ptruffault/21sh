/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 14:40:10 by ptruffau          #+#    #+#             */
/*   Updated: 2018/08/20 14:40:11 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

t_instruct *init_instructions(char *input)
{
	t_instruct *new;
	t_bool first_word;
	char **t;
	int i;

	if (!(new = (t_instruct *)malloc(sizeof(t_instruct))))
		return (NULL);
	if (!(t = ft_correct(ft_strsplit_word(input), envv)))
		return (new);
	i = 0;
	first_word = TRUE;
	while (new[i])
	{
		if (first_word)
		{
			new->bin_path = check_bin(new[i], envv) 
			first_word = FALSE;
		}

	}
}

int main(int ac, char **av, char **e)
{
	t_instruct *i;

	while (42)
	{
		s = correct_syntax(get_input(e));
		i = init_instructions(s);
	}
}
