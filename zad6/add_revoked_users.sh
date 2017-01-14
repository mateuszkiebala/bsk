#!/bin/bash

if [ -z "$@" ];
then
    echo "Arguments not present."
    echo "Usage $0 [list of usernames to revoke]"
    echo "You can get username from [username].csr"
    exit 99
fi

echo "Revoking users..."
for user in "$@"; do
    #Revoke user
    /etc/openvpn/easy-rsa/./revoke-full $user
done
