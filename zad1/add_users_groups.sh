#!/bin/bash

groups=(staff e1 e2 master)
for i in "${groups[@]}"
do
	groupadd $i
done

useradd -M -g master master
useradd -M -g staff staff_1

add_users()
{
	group_name=$1
	group_type=$2
	n=$3
	for i in `seq 1 $n`
	do
		user=424$group_type
		if (( $i < 10 )); then
			user+='0'
		fi
		user+=$i
		useradd -m -g e1 $user
	
		# Select permissions for entering to $user
		chmod g=x,o=- /home/$user
		# Select permissions for files/directories created in $user
		setfacl -dRm u:$user:rwx,g:e1:x,g:staff:x,g:master:rwx,o:- /home/$user
		# Create public directory
		mkdir /home/$user/public
		# Select permissions for files/directories created in $user/public
		setfacl -dRm g:e1:r-x,g:staff:rwx /home/$user/public
		# Select permissions for entering to $user/public
		setfacl -Rm g:e1:r-x,g:staff:r-x /home/$user/public
	done
}

add_users 'e1' 2 2
add_users 'e2' 4 3