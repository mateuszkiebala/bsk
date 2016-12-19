# Mateusz Kiebala 359758

END='\033[0;34m'
BEG='\033[0;32m'
NC='\033[0m' # No Color

echo -e "${BEG}Start mouting files...${NC}"
mkdir /home/guest/bsk_obrazy
sshfs students:/home/students/inf/PUBLIC/BSK/Obrazy /home/guest/bsk_obrazy
echo -e "${END}Mounting done.${NC}\n"

echo -e "${BEG}Start copying files...${NC}"
# additional options: --verbose --progress --stats
rsync --compress --recursive --times --perms --links --delete --exclude "" students:/home/students/inf/PUBLIC/BSK /home/guest/
echo -e "${END}Copying done.${NC}\n"