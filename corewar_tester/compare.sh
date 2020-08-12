./corewar -d $2  $3 $4 $5 $6 > ref.log
$1 -d $2  $3 $4 $5 $6 > we.log
diff we.log ref.log
exit 0
