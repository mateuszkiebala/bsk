# Mateusz Kiebala 359758

# This script should be run on other than server machine
END='\033[0;34m'
BEG='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${BEG}Adding user...${NC}"
sudo useradd -m matkie
echo -e "${END}User added.${NC}\n"

echo -e "${BEG}Change password.${NC}"
sudo passwd matkie
echo -e "${END}Password changing done.${NC}\n"

echo -e "${BEG}Creating RSA key...${NC}"
sudo ssh-keygen -t rsa -f /home/matkie/.ssh/id_rsa
echo -e "${END}Creating done.${NC}\n"

echo -e "${BEG}Copying key to server...${NC}"
sudo ssh-copy-id -i /home/matkie/.ssh/id_rsa guest@server_domain
echo -e "${END}Copying done.${NC}\n"
