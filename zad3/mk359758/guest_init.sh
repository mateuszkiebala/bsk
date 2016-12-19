# Mateusz Kiebala 359758

END='\033[0;34m'
BEG='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${BEG}Creating RSA key...${NC}"
sudo ssh-keygen -t rsa -f /home/guest/.ssh/id_rsa
sudo ssh-add /home/guest/.ssh/id_rsa
# Enter passphrase - password for privte key
# Use ssh-keygen -p -f /home/guest/.ssh/id_rsa for changing passphrase
echo -e "${END}Creating done.${NC}\n"

echo -e "${BEG}Copying keys to servers...${NC}"
# Change client_domain to students machine name.
sudo ssh-copy-id -i /home/guest/.ssh/id_rsa matkie@client_domain
sudo ssh-copy-id -i /home/guest/.ssh/id_rsa mk359758@students.mimuw.edu.pl
echo -e "${END}Copying done.${NC}\n"
