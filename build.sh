#!/bin/bash
set -ex
cmake -B build
cmake --build build -j8
