#debut du mega truc qu'il est trop dur a faire

.name "sub instructions !"
.comment "Verifies that SUB instruction works !"

store:		live %0
start:		or r1, r1, r2
			xor r2, r2, r3
			ld %258, r5
			sub r4, r5, r6
			aff r6
			sti r6, %:loop, %1
			xor r2, r2, r3
loop:		live %42
			zjmp %:loop
