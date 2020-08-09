.name		"Live 1"
.comment	"Live just in time. In same cycle than cycle to die"

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
			and r1,r2,r3
			live %-1
