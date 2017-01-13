#!/bin/bash

#Required
fname=$1
lname=$2
email=$3

#Details
country=PL
state=Mazowieckie
location=Warsaw
organization=MIMUW
organizationalunit=BSK

if [ -z "$fname" ] || [ -z "$lname" ] || [ -z "$email" ];
then
    echo "Arguments not present."
    echo "Usage $0 [first_name last_name email]"
 
    exit 99
fi
 
echo "Generating key request for $fname $lname $email"

domain=$fname$lname
password=dummy

#Generate a key
openssl genrsa -des3 -passout pass:$password -out $domain.key 2048 -noout
 
echo "Removing passphrase from key"
openssl rsa -in $domain.key -passin pass:$password -out $domain.key
 
#Create the request
echo "Creating CSR"
openssl req -new -key $domain.key -out $domain.csr -passin pass:$password \
    -subj "/C=$country/ST=$state/L=$location/O=$organization/OU=$organizationalunit/CN=$domain/emailAddress=$email"
 
#Sign certificate
openssl ca \
    -extensions usr_cert -days 365 -notext \
    -in $domain.csr -out $domain"_cert.pem"

chmod 444 $domain_cert.pem

echo "-------------------------------------------------"
echo "-----Below is your CERTIFICATE VERIFICATION -----"
echo "-------------------------------------------------"
echo
openssl x509 -noout -text -in $domain"_cert.pem"
