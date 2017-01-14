#!/bin/bash

#Run this script in /etc/openvpn/easy-rsa/

echo
echo "---------------------------------"
echo "-----Changing values in vars-----"
echo "---------------------------------"
echo

sed -i 's/.*KEY_COUNTRY=.*/export KEY_COUNTRY="PL"/' vars
sed -i 's/.*KEY_PROVINCE=.*/export KEY_PROVINCE="Mazowieckie"/' vars
sed -i 's/.*KEY_CITY=.*/export KEY_CITY="Warsaw"/' vars
sed -i 's/.*KEY_ORG=.*/export KEY_ORG="MIMUW"/' vars
sed -i 's/.*KEY_EMAIL=.*/export KEY_EMAIL="bsk@mimuw.edu.pl"/' vars
sed -i 's/.*KEY_OU=.*/export KEY_OU="BSK_LAB"/' vars
sed -i 's/.*KEY_CN=.*/export KEY_CN="BSK_CA"/' vars
sed -i 's/.*KEY_NAME=.*/export KEY_NAME="BSK_CA"/' vars
echo 'export KEY_ALTNAMES="something"' >> vars

source vars
./clean-all

echo
echo "---------------------"
echo "-----Creating CA-----"
echo "---------------------"
echo

./build-ca

echo
echo "---------------------"
echo "-----Building dh-----"
echo "---------------------"
echo

./build-dh

echo
echo "-------------------------------------"
echo "-----Creating server certificate-----"
echo "-------------------------------------"
echo

./build-key-server vpn-server
