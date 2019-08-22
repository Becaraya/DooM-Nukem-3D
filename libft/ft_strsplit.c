/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:57:41 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/14 11:29:35 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	**ft_strdel_(char **as)
{
	ft_memdel((void **)as);
	return (NULL);
}

static int		ft_countword(const char *s, char c)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	int		x;
	int		len;
	int		start;
	int		i;
	char	**str;

	if (!s || !(str = (char**)malloc((ft_countword(s, c) + 1) * sizeof(char*))))
		return (NULL);
	x = 0;
	i = 0;
	while (i < ft_countword(s, c))
	{
		len = 0;
		while (s[x] == c && s[x])
			x++;
		start = x;
		while (s[x] != c && s[x++])
			len++;
		if (!(str[i] = ft_strsub(s, start, len)))
			return (ft_strdel_(str));
		i++;
	}
	str[i] = NULL;
	return (str);
}
