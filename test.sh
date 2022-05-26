#!/bin/bash
set -e

# Test Cases
MSG_LEN=10000

MSG1="hello"
MSG2="world"
MSG3=$(yes "0123456789" | tr -d '\n' | head -c $MSG_LEN)

MSGS=($MSG1 $MSG2 $MSG3)
for msg in "${MSGS[@]}"
do
	    EXPECTED+=$msg
done

# Before starting tests, kill all server processes
printf "Before starting tests, kill all server processes...\n\n"
ps | grep "./server" | grep -v grep | awk '{print $1}' | xargs -n1 kill

# Launch server
echo "Launch server"
./server | tail +2 | diff <(printf $EXPECTED) - && printf "\e[1;32mdiff OK:D\n\e[m" || printf "\e[0;31mdiff error\n\e[m" &

# Launch clients continuously
SERVER_PID=$(ps | grep "./server" | grep -v grep | head -1 | awk '{printf $1}')
set -v
for msg in "${MSGS[@]}"
do
	./client $SERVER_PID $msg
done
set +v

# After the tests, kill all server processes
printf "After the tests, kill all server processes...\n\n"
ps | grep "./server" | grep -v grep | awk '{print $1}' | xargs -n1 kill
