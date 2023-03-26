#!/bin/bash

# This script creates new user provided in command line.
# This script auto generates a password.

# Check if running as super user
if [[ ${UID} != "0" ]]
then
  echo "This script must be executed with sudo or by root"
  exit 1
fi

if [[ "${#}" -eq "0"  ]]
then
  echo
  echo "Usage: ${0} USER_NAME [COMMENT]..."
  echo
  exit 1
fi

# The first argument is username
USER_NAME="${1}"

# Rest of arguments form comment
shift
COMMENT="${*}"

# Auto generate a password for new account
PASSWORD=$( date +%s%N | sha256sum | head -c32)

# Add the user
useradd -m ${USER_NAME} -c "${COMMENT}"
exit_status="${?}"

# Return if useradd failed
if [[ $exit_status -ne "0" ]]
then
  echo "Unable to create account for username '${USER_NAME}', with exit status ${exit_status}"
  exit 1
fi

# Set the password for new username
echo $PASSWORD | passwd --stdin ${USER_NAME}

# Prompt the user for new password on first login
passwd -e ${USER_NAME}

# Print the new user details to stdout 
echo ""
echo "New account created."
echo "Username: ${USER_NAME}"
echo "Password: ${PASSWORD}"
echo "Comment: ${COMMENT}"
echo "Hostname: ${HOSTNAME}"
echo ""

exit 0
