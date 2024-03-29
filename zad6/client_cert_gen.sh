#!/bin/bash

#Run this script in /etc/openvpn/easy-rsa/

#Required
fname=$1
lname=$2
email=$3
domain=$fname$lname

if [ -z "$fname" ] || [ -z "$lname" ] || [ -z "$email" ];
then
    echo "Arguments are not present."
    echo "Usage $0 [first_name last_name email client_ip]"
 
    exit 99
fi
 
echo
echo "--------------------------------------------"
echo "-----Generating certificate for $domain-----"
echo "--------------------------------------------"
echo

sed -i 's/.*KEY_EMAIL=.*/export KEY_EMAIL='$email'/' vars
sed -i 's/.*KEY_CN=.*/export KEY_CN='$domain'/' vars
sed -i 's/.*KEY_NAME=.*/export KEY_NAME='$domain'/' vars
source ./vars
./build-key $domain

mkdir "keys/"$domain"_certs"
cp "keys/ca.crt" "keys/"$domain".crt" "keys/"$domain".key" "keys/"$domain"_certs"
