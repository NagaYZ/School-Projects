#!/bin/bash
make clean
make
echo > tests_log.txt

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NOCOLOR='\033[0;37m'

test() {
    files=($1)
    n=0
    passed=0

    for f in ${files[@]}; do
        (( n++ ))
        printf "(%02d/%02d) - %s" $n ${#files[@]} "Testing $f..." | tee -a tests_log.txt
        ./as < $f | { printf "\n"; cat; } >> tests_log.txt
        feedback=$PIPESTATUS      
        if [ "$feedback" = "$2" ]; then
            (( passed++ ))
            if [ "$feedback" == "$2" ]; then
            	printf "${GREEN}"
        		printf "SUCCESS.\n" | tee -a tests_log.txt
        		printf "${NOCOLOR}"            	
        	else
        		printf "${RED}"
            	printf "FAILED.\n" | tee -a tests_log.txt
            	printf "${NOCOLOR}"
        	fi
        fi
        echo >> tests_log.txt
        
    done

    if [ $passed -eq ${#files[@]} ]; then
    	printf "${GREEN}"
		printf "$passed/${#files[@]} tests passed! \n\n" | tee -a tests_log.txt
		printf "${NOCOLOR}"
    elif [ $passed = "0" ]; then
        printf "${RED}"
		printf "$passed/${#files[@]} tests passed! \n\n" | tee -a tests_log.txt
		printf "${NOCOLOR}"
    else
        printf "${YELLOW}"
		printf "$passed/${#files[@]} tests passed! \n\n" | tee -a tests_log.txt
		printf "${NOCOLOR}"
    fi
}
printf "${GREEN}"
printf "=============== Tests corrects ===============\n" | tee -a tests_log.txt
printf "${NOCOLOR}"
test "../tests/corrects/*.tpc" 0

printf "${RED}"
printf "============== Tests incorrects ==============\n" | tee -a tests_log.txt
printf "${NOCOLOR}"
test "../tests/incorrects/*.tpc" 1

echo "Done."