.name "live_only_twice"
.comment "I'M ALIIIIVE"

		and r1 , %0, r2
		ld %:live, r7
		fork %:live
		live %-2
live:	zjmp %:live
fork1:	sti r3, %:live2, %1
live2:	live %-1
		zjmp %:live
