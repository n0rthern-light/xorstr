#!/bin/sh

SOURCE_FILE="main.cpp"
EXECUTABLE="example"
SECRET="very-secret-data"

echo "Compiling as $EXECUTABLE"

clang++ -std=c++23 -Wall -Wextra -O3 "$SOURCE_FILE" -o "$EXECUTABLE" 
chmod +x "$EXECUTABLE" 
echo "Done."
echo "---------------------------------------------"

echo "Output:"
./"$EXECUTABLE"
echo "---------------------------------------------"

echo "Searching secret \"$SECRET\" string in the binary $EXECUTABLE:"

BINARY_OCCURENCES=$(strings "$EXECUTABLE" | grep -F "$SECRET" | wc -l)
echo "$BINARY_OCCURENCES results found."

echo "============================================="

if [ "$BINARY_OCCURENCES" -eq "0" ]; then
  echo "[OK] Strings are encrypted inside the binary"
else
  echo "[FAIL] Secret string have been found in the binary"
  exit 1
fi
