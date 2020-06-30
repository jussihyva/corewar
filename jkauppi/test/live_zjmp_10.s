.name "zork_2"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
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
live10:	zjmp %:live
