#!/bin/bash

# Ensure a file is provided
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 <file> [additional files...]"
    exit 1
fi

# Color codes
RED=$(printf '\033[0;31m')
GREEN=$(printf '\033[0;32m')
YELLOW=$(printf '\033[1;33m')
NC=$(printf '\033[0m') # No Color


# Iterate over all provided files
for file in "$@"; do
    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo -e "${RED}File not found: $file${NC}"
        continue
    fi

    # Run the commands and store the output
    ./ft_nm "$file" > ftnm.out
    nm "$file" > nm.out

    # Compare the outputs
    diff_output=$(diff -u ftnm.out nm.out)

    if [ -n "$diff_output" ]; then
        echo -e "${YELLOW}Differences found for file: $file${NC}"
        echo "Diff result:"
        # Display the diff with color highlighting
       # echo "$diff_output" | sed -e 's/^-/\'$RED'&\'$NC'/' -e 's/^+/\'$GREEN'&\'$NC'/'
	echo "$diff_output" | sed -e "s/^-/$RED&$NC/" -e "s/^+/$GREEN&$NC/"

        # Display the differing sections side by side
       # echo -e "${YELLOW}Displaying differing sections side by side:${NC}"
       # diff -y --suppress-common-lines ftnm.out nm.out | sed -e 's/^/  /' -e 's/|/\'$RED'|\'$NC'/' -e 's/>/\'$GREEN'>\'$NC'/'
	# Display the differing sections side by side
	echo -e "${YELLOW}Displaying differing sections side by side:${NC}"
	diff -y --suppress-common-lines ftnm.out nm.out | sed -e 's/^/ /' -e "s/|/$RED|$NC/" -e "s/>/$GREEN>$NC/"

    else
        echo -e "${GREEN}No differences for file: $file${NC}"
    fi

    # Clean up temporary files
    rm ftnm.out nm.out
done
