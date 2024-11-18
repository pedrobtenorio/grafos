#!/bin/bash

if ! [ -x "./floyd.bin" ]; then
    echo "Error: floyd.bin not found or not executable."
    exit 1
fi

if ! [ -d "testes" ]; then
    echo "Error: 'testes' folder not found."
    exit 1
fi

for file in testes/*.mtx; do
    if [ -f "$file" ]; then
        base_name=$(basename "$file" .mtx)
        echo "Processing file: $base_name"
        output_file="saida/${base_name}-exit.txt"
        mkdir -p saida
        ./floyd.bin -f "$file" -o "$output_file"
        if [ $? -ne 0 ]; then
            echo "Error processing $file. Skipping..."
        fi
    else
        echo "No .mtx files found in the 'testes' folder."
    fi
done
