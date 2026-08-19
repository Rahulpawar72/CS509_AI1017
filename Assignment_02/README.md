CS509 Assignment 2 — Bellman-Ford & Floyd-Warshall
Build
cd "C:\Users\RAHUL PAWAR\OneDrive\Desktop\solo_assignment 2\cs509_a2_solo"
g++ -O2 -Wall -Wextra -std=c++17 -I../Assignment_01/src -o assignment2.exe src/main.cpp ../Assignment_01/src/csr_shared.cpp src/bellman_ford.cpp src/floyd_warshall.cpp

Run
./assignment2

Windows: .\assignment2.exe

You get a simple two-step menu:

===== CS509 Assignment 2 =====
 1) Bellman-Ford
 2) Floyd-Warshall
 0) Exit
Choice:

Pick 1 and it shows Bellman-Ford's test cases (same idea for 2 / Floyd-Warshall):

--- Bellman-Ford Test Cases ---
 1) demo_bf_negative.txt
 2) demo_bf_negcycle.txt
 3) bf_10.txt
 4) bf_100.txt
 5) bf_10000.txt
 6) bf_50000.txt
 7) bf_100000.txt
 0) Back
Choice:

Direct mode (no menu):

./assignment2 bf tests/bellman_ford/bf_10000.txt
./assignment2 fw tests/floyd_warshall/fw_500.txt


Layout
src/      main.cpp, bellman_ford, floyd_warshall
tests/    bellman_ford/  and  floyd_warshall/  test files
tools/    graph_gen.cpp (optional test generator)

CSR is shared from `../Assignment_01/src/csr.hpp` and
`../Assignment_01/src/csr_shared.cpp`; Assignment 2 does not keep a duplicate.
Results


Algorithm	             Test	          V	    E	      Neg Cycle	   Status
Bellman-Ford	demo_bf_negative.txt	  5	    10	      No	        Pass
Bellman-Ford	demo_bf_negcycle.txt	  3	    3	        Yes	        Pass
Bellman-Ford	bf_10.txt	              10	  20	      No	        Pass
Bellman-Ford	bf_100.txt	           100	  300	      No	        Pass
Bellman-Ford	bf_10000.txt	        10,000	30,000	  No	        Pass
Bellman-Ford	bf_50000.txt	        50,000	150,000	  No	        Pass
Bellman-Ford	bf_100000.txt	        100,000	300,000	  No	        Pass
Floyd-Warshall	demo_fw_negative.txt	5	      -       No	        Pass
Floyd-Warshall	demo_fw_negcycle.txt	3	      —	      Yes	        Pass
Floyd-Warshall	fw_10.txt	            10	    —	      No	        Pass
Floyd-Warshall	fw_100.txt	          100	    —	      No	        Pass
Floyd-Warshall	fw_500.txt	          500	    —	      No	        Pass
Floyd-Warshall	fw_1000.txt	          1,000	  —	      No	        Pass
Floyd-Warshall	fw_2000.txt	          2,000  	—	      No	        Pass.
