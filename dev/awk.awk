# NOTE to add " around phone-list.
awk 'BEGIN{FS=",";OFS=","}{ print $0 > "phone-list"}' output.txt

awk '{ print $2 > "phone-list";
print $1 > "name-list" }' BBS-list


awk 'BEGIN{FS=",";OFS=","}{ print $0 > $2".txt" ; print $1}' output.txt



