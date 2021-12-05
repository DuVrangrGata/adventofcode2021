#!/usr/bin/bash

output=$(cat $1)
expected=$(cat $2)

if [ "$output" == "$expected" ]; then
    echo "[Test] Sample Success";
else
    echo "[Test] Sample Failed";
    echo "[Test] Expected: $expected"
    echo "[Test] Got:      $output"
fi
