#!/bin/bash

echo test2 starts
./objdump_x2017 tests/test2.x2017 | diff - tests/test2.mile
./vm_x2017 tests/test2.x2017 | diff - tests/test2.out

echo test2 pass

echo test3 starts
./objdump_x2017 tests/test3.x2017 | diff - tests/test3.mile
./vm_x2017 tests/test3.x2017 | diff - tests/test3.out
echo test3 pass

echo test4 starts
./objdump_x2017 tests/test4.x2017 | diff - tests/test4.mile
./vm_x2017 tests/test4.x2017 | diff - tests/test4.out
echo test4 pass

echo test5 starts
./objdump_x2017 tests/test5.x2017 | diff - tests/test5.mile
./vm_x2017 tests/test5.x2017 | diff - tests/test5.out
echo test5 pass

echo test6 starts
./objdump_x2017 tests/test6.x2017 | diff - tests/test6.mile
./vm_x2017 tests/test6.x2017 | diff - tests/test6.out
echo test6 pass

echo test7 starts
./objdump_x2017 tests/test7.x2017 | diff - tests/test7.mile
./vm_x2017 tests/test7.x2017 | diff - tests/test7.out
echo test7 pass

echo test8 starts
./objdump_x2017 tests/test8.x2017 | diff - tests/test8.mile
./vm_x2017 tests/test8.x2017 | diff - tests/test8.out
echo test8 pass


echo test9 starts
./objdump_x2017 tests/test9.x2017 | diff - tests/test9.mile
./vm_x2017 tests/test9.x2017 | diff - tests/test9.out
echo test9 pass


echo test11 starts
./objdump_x2017 tests/test11.x2017 | diff - tests/test11.mile
./vm_x2017 tests/test11.x2017 | diff - tests/test11.out
echo test11 pass

echo test12 starts
./objdump_x2017 tests/test12.x2017 | diff - tests/test12.mile
./vm_x2017 tests/test12.x2017 | diff - tests/test12.out
echo test12 pass

echo test13 starts
./objdump_x2017 tests/test13.x2017 | diff - tests/test13.mile
./vm_x2017 tests/test13.x2017 | diff - tests/test13.out
echo test13 pass

echo test14 starts
./objdump_x2017 tests/test14.x2017 | diff - tests/test14.mile
echo test14 pass

echo test16 starts
./objdump_x2017 tests/test16.x2017 | diff - tests/test16.mile
echo test16 pass

echo test17 starts
./objdump_x2017 tests/test17.x2017 | diff - tests/test17.mile
echo test17 pass

echo test18 starts
./objdump_x2017 tests/test18.x2017 | diff - tests/test18.mile
echo test18 pass


