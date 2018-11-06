# progressbar
A command-line progress bar written in C


# Installation
`gcc -o progressbar progressbar.c`


# Usage
```
Usage : progressbar <mode> <time> [bar length]
        mode can be
        0 : fullscreen bar (no bar length to provide)
        1 : align right bar (bar length to provide)
```


# Examples
```
./progressbar 0 10
  3 [==================>                                         ] 
```


```
./progressbar 1 10 20
  3                                         [======>             ] 
```
