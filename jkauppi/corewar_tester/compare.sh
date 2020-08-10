../../ProjectInputInformation/corewar -d $1  $2 | egrep "^0x0" > ref.log
../../jhakala/test_dir/prog -dump $1  $2 | egrep "^0x0" > we.log
diff we.log ref.log
exit 0
