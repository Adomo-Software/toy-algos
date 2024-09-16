
N=$1
R=$(($RANDOM % N + 1))
echo $R
( printf "1%.0s" $(seq 1 "$R"); printf "0%.0s" $(seq 1 "$((N - R))") )\
	> data_balls/data_"$N"_"$R"
