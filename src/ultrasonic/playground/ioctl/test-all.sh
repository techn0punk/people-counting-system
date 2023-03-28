#!/bin/sh

printf "Test Sensor 1 (T23 E24): "
./u1

sleep 2

printf "Test Sensor 2 (T25 E16): "
./u2

sleep 2

printf "Test Button OK (PDN17): "
./in 17
echo "Press OK now (2sec)"
sleep 2
printf "Test Button OK (PDN17): "
./in 17

sleep 2

printf "Test Button UP (PDN27): "
./in 27
echo "Press OK now (2sec)"
sleep 2
printf "Test Button UP (PDN27): "
./in 27

sleep 2

echo "Test RED (GPIO 5)"
./out 5 1
sleep 2
./out 5 0

echo "Test YELLOW (GPIO 6)"
./out 6 1
sleep 2
./out 6 0

echo "Test GREEN (GPIO 26)"
./out 26 1
sleep 2
./out 26 0

echo "finish"
