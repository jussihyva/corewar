.name "Indirect_label"
.comment "How indirect jump works"

l2:		sti r1, :indir, %-225
		ldi :indir, %-225, r2
		sti r2, %:live, %1
		and r1, %0, r1
		zjmp %:live

indir:	live %0
live:	live %1
		zjmp %:live
