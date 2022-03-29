/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberdai <aberdai@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:21:40 by aberdai           #+#    #+#             */
/*   Updated: 2022/03/02 00:21:42 by aberdai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define A_KEY_PRSD		0b00000001
# define S_KEY_PRSD		0b00000010
# define D_KEY_PRSD		0b00000100
# define W_KEY_PRSD		0b00001000
# define LEFT_KEY_PRSD	0b00010000
# define RIGHT_KEY_PRSD	0b00100000

typedef enum e_key
{
	A_KEY = 0,
	S_KEY = 1,
	D_KEY = 2,
	W_KEY = 13,
	ESC_KEY = 53,
	LEFT_KEY = 123,
	RIGHT_KEY = 124
}	t_key;

#endif
