.name		"add test"
.comment	"add values which gives result higher than int max."

start:		ld %2147483630, r6
			add r6, r6, r7
			sti r7, :loop, %:loop
			and r2, %0, r2
loop:		live %2
			zjmp %:loop
