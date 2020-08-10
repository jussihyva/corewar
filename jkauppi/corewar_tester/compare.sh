./corewar -d $2  $3 | egrep "^0x0" > ref.log
$1 -dump $2  $3 | egrep "^0x0" > we.log
diff we.log ref.log
exit 0
