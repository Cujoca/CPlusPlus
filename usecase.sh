#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"

echo "=== compiling ==="
cmake --build cmake-build-debug --target Labs 2>&1
echo ""

echo "=== running edge case tests ==="
./cmake-build-debug/Labs << 'EOF'
2
3
4
5
6
7
8
9
1
1
Alice
1001
85
90
95
8
1
2
Bob
1001
1002
45
40
50
Charlie
1003
70
75
80
2
3
1001
3
9999
4
1001

92


4
9999
2
5
9999
6
7
8
1
2
8
2
2
9
10
2
5
1001
5
1002
5
1003
2
11
EOF
