#!/bin/sh

ETH='10.10.2.18'

# Stop any running OPRAPacketMon process
killall OPRAPacketMon

# Monitor Group A 1 ~ 24
./OPRAPacketMon $ETH 233.43.202.1 11101 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.2 11102 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.3 11103 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.4 11104 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.5 11105 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.6 11106 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.7 11107 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.8 11108 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.9 11109 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.10 11110 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.11 11111 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.12 11112 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.13 11113 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.14 11114 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.15 11115 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.16 11116 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.17 11117 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.18 11118 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.19 11119 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.20 11120 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.21 11121 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.22 11122 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.23 11123 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.24 11124 2> /dev/null &

# Monitor Grup A 1 ~ 24
./OPRAPacketMon $ETH 233.43.202.129 16101 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.130 16102 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.131 16103 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.132 16104 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.133 16105 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.134 16106 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.135 16107 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.136 16108 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.137 16109 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.138 16110 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.139 16111 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.140 16112 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.141 16113 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.142 16114 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.143 16115 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.144 16116 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.145 16117 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.146 16118 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.147 16119 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.148 16120 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.149 16121 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.150 16122 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.151 16123 2> /dev/null &
./OPRAPacketMon $ETH 233.43.202.152 16124 2> /dev/null &

# killall -SIGUSR1 OPRAPacketMon && tail -n 48 -f /var/log/messages | grep OPRAPacketMon
