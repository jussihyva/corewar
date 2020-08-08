`../../ProjectInputInformation/corewar -v 31 $1 | grep "It is now cycle" | wc -l > cycles.log`
exit $?
