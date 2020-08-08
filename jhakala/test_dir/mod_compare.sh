echo $1
echo $2
./corewar -d $1  $2 | egrep "^0x0" > ref.log
./prog -dump $1  $2 | egrep "^0x0" > we.log
diff we.log ref.log

