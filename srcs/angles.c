/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 11:15:38 by pitriche          #+#    #+#             */
/*   Updated: 2020/01/28 11:25:08 by ydemange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

inline		t_angle	add_angle(t_angle a1, t_angle a2)
{
	return ((a1 + a2) & D_2PIM);
}

inline		t_angle	sub_angle(t_angle a1, t_angle a2)
{
	if (a1 >= a2)
		return ((a1 - a2) & D_2PIM);
	return (D_2PI - ((a2 - a1) & D_2PIM));
}
