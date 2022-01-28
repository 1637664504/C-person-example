#创建列表
list=("Jack" "lili" "Mark")

#列表遍历:
for i in ${list[*]};do
	echo $i
done
