#!/bin/zsh
#
# Starting from the current directory
start_dir="."

# Find all .c files in the directory and subdirectories
find "$start_dir" -type f -name "*.c" | while read -r file; do
    # Remove the first 11 lines and save it to a temp file
    sed '1,11d' "$file" > "$file.tmp" && mv "$file.tmp" "$file"
    echo "Processed $file"
done

echo "All done. Don't break anything else."

