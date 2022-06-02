# minitalk

## How to use test.sh?
1. Download `test.sh` to your minitalk directory.
2. Run the script `./test.sh`
3. :tada:

<img width="694" alt="Screen Shot 2022-06-02 at 13 18 58" src="https://user-images.githubusercontent.com/7609060/171552262-d729ce9a-868e-4672-be43-3be00a222eab.png">
<img width="692" alt="Screen Shot 2022-06-02 at 13 19 26" src="https://user-images.githubusercontent.com/7609060/171552280-02d6db3d-e0a3-4c6a-8a0d-7787a9d0162a.png">


### Usage Example
```
./tester.sh {length of message} {number of repetition}
```
You can pass `length of message (default 100)` and `number of repetition (default 1)` as arguments.

```
# default (len=100, repeat=1)
./test.sh

# len=1000
./test.sh 1000

# len=100, repeat=10
./test.sh 100 10

# len=10000, repeat=5
./test.sh 10000 5
```
