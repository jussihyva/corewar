.name		"Indirect"
.comment	"Verify content of indirect position in the memory"

		ld :start, r10
		st r10, :stop
start:	aff r10
stop:	live %42
