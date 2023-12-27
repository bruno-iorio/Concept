#!/bin/bash

cmake -S Concept -B build
cmake --build build
./build/ConceptApp
