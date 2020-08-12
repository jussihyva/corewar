$1 -d $2 $3 $4 $5 $6 > we.log
if [ $# -gt 5 ]
then
	param_6=${6}_1
else
	param_6=" "
fi
if [ $# -gt 4 ]
then
	param_5=${5}_1
else
	param_5=" "
fi
if [ $# -gt 3 ]
then
	param_4=${4}_1
else
	param_4=" "
fi
if [ $# -gt 2 ]
then
	param_3=${3}_1
else
	param_3=" "
fi
./corewar -d $2 $param_3 $param_4 $param_5 $param_6 > ref.log
diff we.log ref.log
exit 0
