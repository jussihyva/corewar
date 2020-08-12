.name		"LD STI test"
.comment	"Verify how sti instruction write a value of a register into a memory"

start:	live %1
		ld	%6291456,r4
		sti r4, %:start, %1
		and r5, %0, r5
live:	live %1
		zjmp %:live
