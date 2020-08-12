# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Indirect_label.s                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/09 21:08:25 by ubuntu            #+#    #+#              #
#    Updated: 2020/06/09 23:38:34 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.name "Indirect_label"
.comment "How indirect jump works"

l2:		sti r1, :indir, %-223
		ldi :indir, %-216, r2
		sti r2, %:live, %1
		and r1, %0, r1
		zjmp %:live

indir:	live %0
live:	live %1
		zjmp %:live
