#!/bin/bash
num=$1 #число
dest=$2 #направление
disp=$3 #смещение
value=num
if [ "$dest" == 'l' ];
then 
	echo "Input: $num left $disp" 
	digits=(0 1)
	while true; do
	result=${digits[$((value % 2))]}$result
	value=$((value / 2))
	[[ $value -eq 0 ]] && break
	done
	echo "Reg: $result"
	let "num «= disp" #сдвигает num на disp разряда влево
	echo "Число после сдвига на $disp разряда: $num"
	printf 'Output: %#x\n' "$num"
else
echo "Input: $num rigth $disp"
digits=(0 1)
while true; do
result=${digits[$((value % 2))]}$result
value=$((value / 2))
[[ $value -eq 0 ]] && break
done
echo "Reg: $result"
let "num »= disp" #сдвигает num на disp разряда вправо
echo "Число после сдвига на $disp разряда: $num"
printf 'Output: %#x\n' "$num"
fi
