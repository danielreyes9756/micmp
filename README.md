# My own file comparator
I developed my own file comparator this program it serves to compare a even number of files, can list and jump being this last two optinal
* -l to list the files with a 1024 bytes buffer
* -i to jump n bytes of the file
## How to test 
* create a compile file 
```
 gcc micmp.c micmpMain.c "this command create a default file to compile called a.out, to change the name use -o name" 
 ```
* execute
```
 ./a.out [-i n1:n2 -l] namefiles
