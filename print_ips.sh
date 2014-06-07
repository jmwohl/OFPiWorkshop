#!/bin/bash

ip addr show wlan0 | grep -Eo "[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}" |

while read x; do
echo $x;
done