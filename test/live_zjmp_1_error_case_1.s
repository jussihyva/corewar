.name "live_zjmp_1_error_case_1"
.comment "I'M ALIIIIVE"

		sti r1, %:live, %1
live:	live %1
		zjmp %:live
		and r1, %0, r2
