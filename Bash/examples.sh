
# Bash script to calculate the frequency of each word in a text file words.txt.
cat words.txt | tr -s ' ' '\n' | sort | uniq -c | sort -r | awk '{print $2 " " $1}'

# Print 10th line of abcd.txt.
# Use sed to print 10th line.
sed -n 10p abcd.txt 
# OR
# Read a file into array and print 10th element of array.
readarray -n 10 -t arr < 'abcd.txt' && echo "${arr[9]}"
# OR
# Tail the file starting from 10th line and then print 1 line.
tail -n+10 abcd.txt | head -n1

# Compare two binary files.
cmp -l bin_file_1 bin_file_2 | gawk '{printf "%08X %02X %02X\n", $1, strtonum(0$2), strtonum(0$3)}'
