#!/bin/bash

fname=$1
lname=$2
client_ip=$3
domain=$fname$lname

if [  -z "$fname" ] || [ -z "$lname" ] || [ -z "$client_ip" ];
then
    echo "Arguments are not present."
    echo "Usage $0 [first_name last_name client_ip]"
 
    exit 99
fi

echo
echo "---------------------------------------"
echo "-----Copying certificate to client-----"
echo "---------------------------------------"
echo

scp -r "keys/"$domain"_certs" guest@$client_ip:/home/guest/