#debut du mega truc qu'il est trop dur a faire

.name "ld st instructions !"
.comment "Verifies that LD and ST works !"

store:		live %0
start:		sti r1, :store, %-1
			ldi :store, %-1, r2
			sti r2, :loop, %1
			and r3, %0, r4
loop:		live %42
