#!/bin/bash

RED='\033[0;31m'
NC='\033[0m' # No Color
GREEN='\033[0;32m'
BLUE='\033[0;34m'

echo -e "${GREEN}Comparing has started!${NC}"
echo
for file in ./*.in; do
    printf "%s\n" $file
    printf "My set:\n"
    time ../../build/level-01/level-01 < $file
    printf "std::set:\n"
    time ../../build/level-01/level-01-std-set < $file
    printf "\n" 
done