#debut du mega truc qu'il est trop dur a faire

.name "ld st instructions !"
.comment "Verifies that LD and ST works !"

store:		live %0
start:		or r1, r1, r2
			xor r2, r2, r3
			ld %2, r5
			add r4, r5, r6
			aff r6
			add r6, r5, r6
			aff r6
			sti r6, :loop, %1
			xor r2, r2, r3
loop:		live %42
			zjmp %:loop
