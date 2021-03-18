#!/bin/bash

function mergeFiles () {
	sub_eras=("$@")
	cmsera=${sub_eras[1]:0:1}
	merge_dir=$output_dir/2018/$cmsera
	mkdir -p $merge_dir
	echo "Created $merge_dir"

	for i in `ls $output_dir/2018/${sub_eras[1]}/*.root`
	do 
		filename=`basename $i`
		files_to_merge=""
		nEvents="0"
		for sub_era in ${sub_eras[@]}
		do 
			files_to_merge="$files_to_merge $output_dir/2018/$sub_era/$filename"
			nEvents_line=(`grep 'TrigReport Events total' "signalNTuples_v2/2018/$sub_era/${filename%.*}.out"`)
			nEvents=$(($nEvents + ${nEvents_line[4]}))
		done 

		hadd $merge_dir/$filename ${files_to_merge[@]}
		echo "TrigReport Events total = $nEvents" > $merge_dir/${filename%.*}.out
	done
}

output_dir="signalNTuples_v2"

pack1=("B1" "B2")
pack2=("D1" "D2")

mergeFiles ${pack1[@]}
mergeFiles ${pack2[@]}