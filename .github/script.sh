ba_files=`ls ../testFiles/*.ba`
for file in $ba_files
do
  filename="${file%.*}"
  printf "%s\n\n" $filename
  wait $(./BigAdd $filename)
  printf "\n\n"
done
