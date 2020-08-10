.name		"sub test"
.comment	"sub values which gives result below 0."

start:		ld %2147483620, r6
			sub r6, r5, r7
			sti r7, :loop, %:loop
			and r2, %0, r2
loop:		live %2
			zjmp %:loop
