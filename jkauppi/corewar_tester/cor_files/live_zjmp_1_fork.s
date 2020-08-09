.name "live_zjmp_10"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		sti r1, %:live1, %1
		and r2, %0, r2

live:	live %1
		fork %:live
live1:	live %1
		zjmp %:live1
