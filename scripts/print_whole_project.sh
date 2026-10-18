#!/bin/bash
find $1 -type f \( -name "*.cpp" -o -name "*.h" \) -exec sh -c 'echo -e "\n\033[1;36m=== Файл: {}\033[0m\n"; cat {}; echo' \;

for i in README.md CMakeLists.txt; do
    echo -e "\n\033[1;36m=== Файл: $i\033[0m\n"
    cat "$1"/../$i
    echo
done
