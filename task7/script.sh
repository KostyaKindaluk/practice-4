gcc main.c -o main.exe

if [[ "$1" == "-ltrace" ]]; then
  ltrace ./main.exe
else
  ./main.exe
fi