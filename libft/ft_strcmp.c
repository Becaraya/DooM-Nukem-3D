/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: becaraya <becaraya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 17:13:14 by becaraya          #+#    #+#             */
/*   Updated: 2018/11/09 15:23:03 by becaraya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;
	int result;

	i = 0;
	while ((int)s1[i] != 0 && (int)s2[i] != 0 && (int)s1[i] == (int)s2[i])
		i++;
	result = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
	return (result);
}
