# build.sh
# Copyright (c) 2021, Jacopo Maltagliati
# Released under the BSD 3-Clause License.
clear
pushd AllocTracker
printf "\n\n\n"
gcc allocTracker.c main.c -o leakTest
echo "Leak test w/ malloc()"
valgrind --leak-check=full ./leakTest
printf "\n\n\n"
gcc allocTracker.c main.c -DUSE_ALLOC_TRACKER -o leakTest
echo "Leak test w/ allocTrackerNew()"
valgrind --leak-check=full  ./leakTest
rm leakTest
printf "\n\n\n"
popd