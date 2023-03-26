#!/bin/bash

# Check if running as super user
if [[ ${UID} != "0" ]]
then
  echo "This script must be executed only by root"
  exit 1
fi

# Prompt for real name
read -p 'Enter your desired real name: ' COMMENT

# Prompt user for username
read -p 'Enter your desired username: ' USER_NAME

# Prompt user for password
read -p 'Enter your desired password: ' PASSWORD

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
echo "Real Name: ${COMMENT}"
echo "Username: ${USER_NAME}"
echo "Password: ${PASSWORD}"
echo "Hostname: ${HOSTNAME}"
echo ""

exit 0
