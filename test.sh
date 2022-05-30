#!/bin/bash
center() {
  termwidth="$(tput cols)"
  padding="$(printf '%0.1s' ={1..500})"
  printf '%*.*s %s %*.*s\n' 0 "$(((termwidth-2-${#1})/2))" "$padding" "$1" 0 "$(((termwidth-1-${#1})/2))" "$padding"
}
# Test Configuration
MSG_LEN=${1:-100}
NUM_REPEAT=${2:-1}
center "Test Config"
printf "NUM_REAPEAT=$NUM_REPEAT\nMSG_LEN=$MSG_LEN\n\n"

# Test Cases
messages+=("hello")
messages+=("world")
messages+=("ã‚¢ã‚¤ã‚¦ã‚¨ã‚ªí ½í¸‚í ½í¸‚í ½í¸‚")
messages+=("$(jot -n -s "" -b "$(jot -n -s "" -c 96 32)" 0 | head -c $MSG_LEN)")

for msg in "${messages[@]}"
do
	combined_message+=$msg
done

success=0
total=0

# Before starting tests, kill all server processes
ps | grep "./server" | grep -v grep | awk '{print $1}' | xargs -n1 kill

center "Invalid arguments"
	./server &
	pid=$(ps | grep "./server" | grep -v grep | head -1 | awk '{printf $1}')
	((total+=1))
	printf "./client\n"
	./client && printf "\e[0;31m[$total] Error is not handled.\n\e[m" || printf "\e[1;32m[$total] Error handling OK:D\n\e[m" && ((success+=1))

	((total+=1))
	printf "./client $pid\n"
	./client $pid && printf "\e[0;31m[$total] Error is not handled.\n\e[m" || printf "\e[1;32m[$total] Error handling OK:D\n\e[m" && ((success+=1))

	((total+=1))
	printf "./client $pid hello world\n"
	./client $pid hello world && printf "\e[0;31m[$total] Error is not handled.\n\e[m" || printf "\e[1;32m[$total] Error handling OK:D\n\e[m" && ((success+=1))

	((total+=1))
	printf "./client 0 hello\n"
	./client 0 hello && printf "\e[0;31m[$total] Error is not handled.\n\e[m" || printf "\e[1;32m[$total] Error handling OK:D\n\e[m" && ((success+=1))

	((total+=1))
	printf "./client 1 hello\n"
	./client 1 hello && printf "\e[0;31m[$total] Error is not handled.\n\e[m" || printf "\e[1;32m[$total] Error handling OK:D\n\e[m" && ((success+=1))

	((total+=1))
	printf "./client 99 hello\n"
	./client 99 hello && printf "\e[0;31m[$total] Error is not handled.\n\e[m" || printf "\e[1;32m[$total] Error handling OK:D\n\e[m" && ((success+=1))

	((total+=1))
	printf "./client 10000000 hello\n"
	./client 10000000 hello && printf "\e[0;31m[$total] Error is not handled.\n\e[m" || printf "\e[1;32m[$total] Error handling OK:D\n\e[m" && ((success+=1))

	((total+=1))
	printf "./client 10000000000000 hello\n"
	./client 10000000000000 hello && printf "\e[0;31m[$total] Error is not handled.\n\e[m" || printf "\e[1;32m[$total] Error handling OK:D\n\e[m" && ((success+=1))

	((total+=1))
	printf "./client abcde hello\n"
	./client abcde hello && printf "\e[0;31m[$total] Error is not handled.\n\e[m" || printf "\e[1;32m[$total] Error handling OK:D\n\e[m" && ((success+=1))

	((total+=1))
	printf "./client "$pid"abcde hello\n"
	./client "$pid"abcde hello && printf "\e[0;31m[$total] Error is not handled.\n\e[m" || printf "\e[1;32m[$total] Error handling OK:D\n\e[m" && ((success+=1))

	ps | grep "./server" | grep -v grep | awk '{print $1}' | xargs -n1 kill

for (( i = 0; i < $NUM_REPEAT; i++ ))
do
	# 1. Testing a message from single process
	printf "\n\n"
	center "Message from a single process"
	for msg in "${messages[@]}"
	do
		((total+=1))
		./server | tail +2 | diff <(printf "%s" "$msg") - &
		pid=$(ps | grep "./server" | grep -v grep | head -1 | awk '{printf $1}')
		printf "./client $pid %s\n" "$msg"
		./client $pid "$msg"
		ps | grep "./server" | grep -v grep | awk '{print $1}' | xargs -n1 kill
		wait $! && printf "\e[1;32m[$total] diff OK:D\n\e[m" && ((success+=1)) || printf "\e[0;31m[$total] diff error\n\e[m"
	done

	# 2. Testing messages from multiple processes in a row
	printf "\n\n"
	center "Messages from multiple processes in a row"
	((total+=1))
	./server | tail +2 | diff <(printf "%s" "$combined_message") - &
	pid=$(ps | grep "./server" | grep -v grep | head -1 | awk '{printf $1}')
	for msg in "${messages[@]}"
	do
		printf "./client $pid %s\n" "$msg"
		./client $pid "$msg"
	done

	# After the tests, kill all server processes
	ps | grep "./server" | grep -v grep | awk '{print $1}' | xargs -n1 kill
	wait $! && printf "\e[1;32m[$total] diff OK:D\n\e[m" && ((success+=1)) || printf "\e[0;31m[$total] diff error\n\e[m"
done

if [ $success == $total ]
then
	printf "\n\e[1;32mAll $total tests passed!\n\e[m";
else
	printf "\n\e[1;31m$((total - success)) tests failed. $success tests passed.\n\e[m";
fi
