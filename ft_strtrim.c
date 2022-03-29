/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:23 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:21:24 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_inset(char c, char const *set)
{
	int	len;

	len = -1;
	while (set[++len])
		if (c == set[len])
			return (1);
	return (0);
}

static char	*ft_nullstr(void)
{
	char	*s;

	s = (char *)malloc(sizeof(char));
	if (!s)
		return (NULL);
	s[0] = '\0';
	return (s);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*t;
	size_t	l;
	size_t	r;
	size_t	ln;

	l = 0;
	while (l < ft_strlen(s1) && ft_inset(s1[l], set))
		l++;
	r = ft_strlen(s1) - 1;
	while (r && ft_inset(s1[r], set))
		r--;
	if (r >= l)
	{
		ln = r - l + 1;
		t = (char *)malloc(sizeof(char) * (ln + 1));
		if (!t)
			return (NULL);
		r = 0;
		while (r < ln)
			t[r++] = s1[l++];
		t[r] = '\0';
		return (t);
	}
	return (ft_nullstr());
}
