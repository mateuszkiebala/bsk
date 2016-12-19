# Mateusz Kiebala 359758

END='\033[0;34m'
BEG='\033[0;32m'
NC='\033[0m' # No Color

# Script goal:
# mk359758 will be default username when logging into students
echo -e "${BEG}Adding configuration to guest ssh.${NC}"
touch /home/guest/.ssh/config
echo -e 'Host students \n\t HostName students.mimuw.edu.pl \n\t User mk359758' >> /home/guest/.ssh/config
echo -e "${END}Configuration added.${NC}\n"
