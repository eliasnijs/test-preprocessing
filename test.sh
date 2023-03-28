#!/bin/sh

# NOTE(Elias): Compile
build/c-preproc resources/1.c resources/.mfttmp.c
gcc resources/.mfttmp.c -o mfttests_

# NOTE(Elias): Run tests
./mfttests_

# NOTE(Elias): cleanup
rm mfttests_
rm resources/.mfttmp.c
