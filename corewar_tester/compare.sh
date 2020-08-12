./corewar -d $2  $3 $4 $5 $6 | egrep "^0x0" > ref.log
$1 -d $2  $3 $4 $5 $6 | egrep "^0x0" > we.log
diff we.log ref.log
exit 0
