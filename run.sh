#!/usr/bin/env bash

cmake --build build -j $(nproc) && ./build/omdi-demo
