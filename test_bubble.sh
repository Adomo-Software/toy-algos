
N=$1
	# > data_balls/data_"$N"_"$R"

# tr -dc '0-9' </dev/urandom | head -c $N; echo

seq 1 $N | shuf | head -n $N
