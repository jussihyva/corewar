/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:14:20 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/13 18:53:49 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct			s_player
{
	header_t			*header;
	int					id;
	char				*file_name;
	char				*input;
	struct s_player		*next;
}						t_player;

typedef struct			s_mem
{
	int					dump;
	int					n_player;
	struct s_player		*player;
}						t_mem;

#endif
