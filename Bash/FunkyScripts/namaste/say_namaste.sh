input_file="/home/abhay/PersonalConfigs/namaste.txt"
num_lines=$(wc -l < "$input_file")
selected_line=$(shuf -i 1-$num_lines -n1)
curr_line=0
while read -r line; 
do
  curr_line=$(( $curr_line + 1 ))
  if [ "$curr_line" -eq "$selected_line" ] 
  then
    language=$(echo $line | awk '{print $1}')
    greeting=$(echo $line | awk '{print $2}')
    echo "$greeting $USER! (in $language)"
    break
  fi
done < "$input_file"

