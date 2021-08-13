#!/usr/bin/env bash

# Source this file for changes in PATH to actually take effect
# Run: . ./append_cur_to_path.sh

case "$PATH" in
    *"$(pwd)"*) 
        ;;
    *)
    PATH="$PATH:$(pwd)"
esac

