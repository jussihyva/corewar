.name "live_only_once"
.comment "I'M ALIIIIVE"

		live %-7
		and r1, %1, r2
live:	zjmp %:live
