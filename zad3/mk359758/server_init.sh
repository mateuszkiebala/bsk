# Mateusz Kiebala 359758

END='\033[0;34m'
BEG='\033[0;32m'
NC='\033[0m' # No Color

# This should be run on guest machine

echo -e "${BEG}Start update...${NC}"
sudo apt-get update
sudo apt-get install openssh-server rsync sshfs
echo -e "${END}Update done.${NC}\n"

echo -e "${BEG}Adding user...${NC}"
sudo useradd -m matkie
echo -e "${END}User added.${NC}\n"

echo -e "${BEG}Change password${NC}"
sudo passwd matkie
echo -e "${END}Password changed.${NC}\n"