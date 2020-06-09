# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Indirect_label.s                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 21:08:25 by ubuntu            #+#    #+#              #
#    Updated: 2020/06/09 21:23:30 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.name "Indirect_label"
.comment "How indirect jump works"

l2:		sti r1, %:live, %0
		ld %-5, r2;
		sti r2, %:indir, %0
		and r1, %0, r1

indir:	zjmp %:l2
live:	live %1
		zjmp :indir
