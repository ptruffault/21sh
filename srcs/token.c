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


t_token *new_token(t_token *prev)
{
	t_token *new;

	if (!(new = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	new->t = NULL;
	new->cmd = NULL;
	new->prev = prev;
	new->next = NULL;
	return (new);
}

void check_token(char *s, t_redirect)
{
	if (*s == '>' && *(s + 1) == '>')
		r->t = >>;
	else if (*s == '>')
		r->t = >;
	else if (*s == '<' && *s == '<')
		r->t = <<;
	else if (*s == '<')
		r->t = <;
	else if (*s == '|')
		r->t = |;
	else
		r->t = ?;
}

t_token *ft_addtoken(t_token *t, char *input, int i)
{
	if (IS_REDIRECTION(input[i]))
	{

	}
}

t_token *init_token(char *input, envv)
{
	t_token *t;
	int i;

	i = 0;
	if (!(t = new_token(NULL)))
		return (NULL);
	while (input[i])
	{
		if (IS_TOKEN(input[i]))
		{
			t = ft_addtoken(t, input, i);
			t->next = new_token(t);
			t = t->next;
		}
		i++;
	}
}

t_token *get_token(char *input, t_envv *envv)
{
	t_token *t;
	char **words;

	t = init_token(input, envv);
	return (t);
}