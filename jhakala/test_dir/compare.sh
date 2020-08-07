echo $1
../../ProjectInputInformation/corewar -d $1  ../../jkauppi/test/Gagnant.cor | egrep "^0x0" > ref.log
./prog -dump $1  ../../jkauppi/test/Gagnant.cor | egrep "^0x0" > we.log
diff we.log ref.log

