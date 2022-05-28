#!/bin/bash
set -e

# Test Cases
MSG_LEN=1000
printf "MSG_LEN=$MSG_LEN\n"

MSG1="hello"
MSG2="world"
MSG3=$(yes "0123456789" | tr -d '\n' | head -c $MSG_LEN)

MSGS=($MSG1 $MSG2 $MSG3)
for msg in "${MSGS[@]}"
do
	    EXPECTED+=$msg
done

# Before starting tests, kill all server processes
ps | grep "./server" | grep -v grep | awk '{print $1}' | xargs -n1 kill

# 1. Testing a message from single process
printf "[1. Testing a message from single process]\n"
for msg in "${MSGS[@]}"
do
	./server | tail +2 | diff <(printf $msg) - && printf "\e[1;32mdiff OK:D\n\e[m" || printf "\e[0;31mdiff error\n\e[m" &
	SERVER_PID=$(ps | grep "./server" | grep -v grep | head -1 | awk '{printf $1}')
	printf "./client $SERVER_PID $msg\n"
	./client $SERVER_PID $msg
	ps | grep "./server" | grep -v grep | awk '{print $1}' | xargs -n1 kill
done

sleep 0.1
printf "\n\n"

# 2. Testing messages from multiple processes in a row
printf "[2. Testing messages from multiple processes in a row]\n"
./server | tail +2 | diff <(printf $EXPECTED) - && printf "\e[1;32mdiff OK:D\n\e[m" || printf "\e[0;31mdiff error\n\e[m" &
SERVER_PID=$(ps | grep "./server" | grep -v grep | head -1 | awk '{printf $1}')
for msg in "${MSGS[@]}"
do
	printf "./client $SERVER_PID $msg\n"
	./client $SERVER_PID $msg
done

# After the tests, kill all server processes
ps | grep "./server" | grep -v grep | awk '{print $1}' | xargs -n1 kill
