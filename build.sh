mkdir -p bin
gcc -std=c17 -Wall -Wextra -o bin/vertac src/main.c src/lexer.c src/utils.c src/parser.c
