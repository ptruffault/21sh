/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptruffau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 14:11:06 by ptruffau          #+#    #+#             */
/*   Updated: 2018/07/04 14:11:07 by ptruffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <21sh.h>

char *ft_exp_param(char *ret, t_shell *sh, char *ptr);

//return VAR pour $VAR/lol
static char *ft_get_varname(char *s)
{
	char *ptr;
	int i;

	i = 0;
	ptr = s + 1;
	while (ptr[i] && (ft_isalpha(ptr[i]) || ptr[i] == '_'))
		i++;
	return (ft_strsub(s, ptr - s , i));
}


//gére le $VAR
static char *ft_exp_envv_var(char *ret, char *ptr, t_shell *sh)
{
	char *name;
	char *value;
	char *tmp;

	name = ft_get_varname(ptr);
	if (!(value = get_tenvv_val(sh->env, name)))
		value = get_tenvv_val(sh->intern, name);
	if ((tmp = ft_strpull(ret, ptr , ft_strlen(name) + 1, value)))
	{
		ft_strdel(&ret);
		ret = tmp;
	}
	ft_strdel(&name);
	return (ret);
}

//gére le ~
static char *ft_exp_home_var(char *ret, char *ptr, t_envv *envv)
{
	char *tmp;

	if ((tmp = ft_strpull(ret, ptr, 1, get_tenvv_val(envv, "HOME"))))
	{
		ft_strdel(&ret);
		return(tmp);
	}
	return (NULL);
}

//return la taille d'une parrenthése meme s'il i ya des parenthéses dedan
static int get_content_size(char *s)
{
	int i;

	i = 2;
	while (s[i] && s[i] != '}')
	{
		if (s[i] == '$' && s[i + 1] == '{')
			i = i + get_content_size(&s[i]) + 2;
		i++;
	}
	return (i - 2);
}

char *handle_modifier(char *parenth, char *ptr, t_shell *sh)
{
	char *val;
	char *val1;
	char *val2;


	val = NULL;
	if (!(val1 = ft_strsub(parenth, 0, ptr - parenth - 1)))
		return (NULL);
	val2 = ft_strdup(ptr + 1);
	if (*ptr == '-' && !(val = ft_strdup(get_tenvv_val(sh->env, val1))))
		val = ft_strdup(val2);
	if (*ptr == '+')
		val = (get_tenvv(sh->env, val1) ? ft_strdup(val2) : NULL);
	if (*ptr == '?' && !(val = ft_strdup(get_tenvv_val(sh->env, val1))))
		error(val1, val2);
	if (*ptr == '=' && !(val = ft_strdup(get_tenvv_val(sh->env, val1))) && val2 && 
	(sh->env = ft_new_envv(sh->env, val1, val2)))
		val = ft_strdup(val2);
	ft_strdel(&val1);
	ft_strdel(&val2);
	return (val);
}


char *sub_handle_modifier(char *parenth, char *ptr, t_shell *sh)
{
	char *v1;
	char *v2;
	char *val;

	if (!(v1 = ft_strndup(parenth, ptr - parenth)))
		return (NULL);
	v2 = ft_strdup(ptr + 1);
	val = NULL;
	if (*ptr == '-')
		val = ft_strdup((get_tenvv(sh->env, v1) ? v1 : v2));
	if (*ptr == '+')
		val = ft_strdup((get_tenvv(sh->env, v1) ? v2 : NULL));
	if (*ptr == '?' && !(val = ft_strdup((get_tenvv(sh->env, v1) ? v1 : NULL))))
		error(v1, v2);
	if (*ptr == '=' && !(val = ft_strdup((get_tenvv(sh->env, v1) ? v1 : NULL))) && v2 && 
	(sh->env = ft_new_envv(sh->env, v1, v2)))
		val = ft_strdup(v2);
	ft_strdel(&v1);
	ft_strdel(&v2);
	return (val);
}

//gére ${${...}}
char *sub_get_param_value(char *old_parenth, t_shell *sh)
{
	char *parenth;
	char *value;
	char *ptr;

	if (!(parenth = ft_strsub(old_parenth, 2, get_content_size(old_parenth))))
		return (NULL);
	value = NULL;
	if (ft_str_startwith(parenth, "${"))
		parenth = sub_get_param_value(parenth, sh);
	if ((ptr = ft_strchr(parenth, ':')) && ++ptr)
	{
		if (ft_strchr("-+?=", *ptr))
		{
			value = sub_handle_modifier(parenth, ptr, sh);
		}
		else
			error_c("unrecognized modifier", *ptr);
	}
	else
		value = ft_strdup(parenth);
	printf("subvalue = %s\n",value );
	return (ft_strpull(old_parenth, old_parenth , get_content_size(old_parenth) + 2 , value));
}

char *ft_get_param_value(t_shell *sh, char *parenth)
{
	char *ptr;
	char *val;

	val = NULL;
	if ((ptr = ft_strchr(parenth, ':')) && ++ptr)
	{
		if (ft_strchr("-+?=", *ptr))
			val = handle_modifier(parenth, ptr, sh);
		else
			error_c("unrecognized modifier", *ptr);
	}
	else
		val = ft_strdup(get_tenvv_val(sh->env, parenth));
	ft_strdel(&parenth);
	return (val);

}

char *ft_exp_param(char *ret, t_shell *sh, char *ptr)
{	
	char *value;
	char *tmp;
	char *parenth;

	if (!(parenth = ft_strsub(ret, ptr - ret + 2 ,  get_content_size(ptr))))
		return (NULL);
	if (*parenth == '#' &&  (tmp = ft_get_param_value(sh, parenth)))
	{
		value = ft_itoa(ft_strlen(tmp));
		ft_strdel(&tmp);
	}
	else
	{
		if (ft_str_startwith(parenth, "${"))
			parenth = sub_get_param_value(parenth, sh);
		printf("parenth post sub = \n%s\n",parenth );
		value = ft_get_param_value(sh, parenth);
	}
	if ((tmp = ft_strpull(ret, ptr, get_content_size(ptr) + 3, value)))
	{
		ft_strdel(&ret);
		ret = tmp;
	}
	ft_strdel(&value);
	return (ret);
}


char  *ft_exp_var(char *ret, t_shell *sh)
{
	int i;

	i = 0;
	while (ret && ret[i])
	{
		if (ret[i] == '~')
			ret = ft_exp_home_var(ret, &ret[i], sh->env);
		if ((ret[i] == '$') && ret[i+ 1] == '{')
			ret = ft_exp_param(ret, sh, &ret[i]);
		if ((ret[i] == '$') && ret[i + 1] != '{')
			ret = ft_exp_envv_var(ret, &ret[i], sh);
		i++;
	}
	return (ret);
}