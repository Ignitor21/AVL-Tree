#!/bin/bash

RED='\033[0;31m'
NC='\033[0m' # No Color
GREEN='\033[0;32m'
BLUE='\033[0;34m'

echo -e "${GREEN}Comparing has started!${NC}"
echo
for file in ../end-to-end/*.in; do
    printf "%s\n" $file
    ../../build/level-01/comparing/main-compare < $file
    ../../build/level-01/comparing/std-set-compare < $file
    printf "\n" 
done