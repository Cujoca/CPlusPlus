#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"

echo "=== compiling ==="
cmake --build cmake-build-debug --target Labs 2>&1
echo ""

echo "=== running edge case tests ==="
# One stdin stream: the student menu runs first, then the employee menu takes over
# once 11 is entered. Comments cannot go inside the heredoc (every line there is
# fed to the program as input), so each test is listed here against its inputs.
#
# STUDENT MENU
#   2 3 4 5 6 7 8 9        every action on an empty roster -> safe message, no data
#   1 1 Alice 1001 ...     add one student (marks 85 90 95)
#   8                      sort with one student -> "Not enough students to sort."
#   1 2 Bob 1001 ...       add two; Bob's ID 1001 is a duplicate -> re-prompt, 1002 ok
#   2                      display all three
#   3 1001                 search, found
#   3 9999                 search, no match
#   4 1001 _ 92 _ _        edit Alice: blank keeps name, mark 1 -> 92, blanks keep 2 & 3
#   4 9999                 edit, no match
#   5 9999                 delete, no match
#   6                      highest scorer
#   7                      class summary
#   8 1 / 8 2              sort by name, then by average (display after each)
#   9 / 10                 save to file, then load back
#   5 1001 / 5 1002 / 5 1003   delete every student, then display the empty roster
#   11                     exit to the employee menu
#
# EMPLOYEE MENU
#   2                      display on an empty roster -> "No employees to display."
#   3                      highest paid with no data -> "No employees on record."
#   abc / 9                menu choice rejected: non-numeric, then out of range
#   1 5 1 _ Alice ...      type 5 rejected, blank name rejected; salaried 50000 + 5000 = 55000
#   1 2 Bob 200 40 ...     hours 200 rejected (>168); rate 5 and 17.94 rejected below
#                          minimum wage, 17.95 accepted -> 40 * 17.95 = 718
#   1 3 Carl ...           commission rate 1.5 rejected; 30000 + 100000 * 0.15 = 45000
#   1 1 Dave -100 ...      salary -100 rejected as negative; 70000 + 0 = 70000
#   2                      display all four -> multiple additions in one session
#   3                      highest paid across all three types -> Dave at 70000
#   4                      exit
#
# ( _ marks a deliberately blank line )
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
2
3
abc
9
1
5
1

Alice
50000
5000
1
2
Bob
200
40
5
17.94
17.95
1
3
Carl
30000
100000
1.5
0.15
1
1
Dave
-100
70000
0
2
3
4
EOF
