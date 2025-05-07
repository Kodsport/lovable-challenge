echo "Running verifyproblem ${@:1} -l debug > /tmp/analysis 2> /dev/null"
verifyproblem ${@:1} -l debug > /tmp/analysis 2> /dev/null
python3 "${0%/*}"/analyzetestgroups.py --file /tmp/analysis $1
