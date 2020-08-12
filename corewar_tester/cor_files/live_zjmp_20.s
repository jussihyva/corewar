.name "live_zjmp_20"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r2, %0, r2

live:	live %1
		fork %:live
		zjmp %:live1
live1:	zjmp %:live2
live2:	zjmp %:live3
live3:	zjmp %:live4
live4:	zjmp %:live5
live5:	zjmp %:live6
live6:	zjmp %:live7
live7:	zjmp %:live8
live8:	zjmp %:live9
live9:	zjmp %:live10
live10:	zjmp %:live11
live11:	zjmp %:live12
live12:	zjmp %:live13
live13:	zjmp %:live14
live14:	zjmp %:live15
live15:	zjmp %:live16
live16:	zjmp %:live17
live17:	zjmp %:live18
live18:	zjmp %:live19
live19:	zjmp %:live20
live20:	zjmp %:live
