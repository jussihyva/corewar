.name		"Live 2"
.comment	"Live just too late. In one cycle later than cycle to die"

start:		zjmp %:lfork
			lfork %:lfork
lfork:		lldi r1,r2,r3
			lldi r1,r2,r3
			lldi r1,r2,r3
			lldi r1,r2,r3
			lldi r1,r2,r3
			lldi r1,r2,r3
			lldi r1,r2,r3
			lldi r1,r2,r3
			lldi r1,r2,r3
			lldi r1,r2,r3
			aff r1
			ld %2, r2
			live %-1
