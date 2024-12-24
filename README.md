# CS201-Homework-PandemicSimulator


Welcome to the City of Contagion!
Hold tight to your face masks — it’s time to simulate the spread of a pandemic in a city,
and only you will uncover its fate!
Imagine a city represented as an m×ngrid, where each cell tells a story:
0 : An empty block, perhaps a park, or maybe just an abandoned building.
1 : A block with healthy individuals, living their best lives (at least for now).
2 : An infected block with infected individuals, ready to spread the infection.
Figure 1: Spread of the pandemic at each time step
Every day, the infection spreads from each infected block to any adjacent healthy block
only, horizontally or vertically. It cannot spread diagonally and it cannot spread to empty
blocks. Your mission, should you choose to accept it:
Calculate the minimum time (number of days) it will take for the infection to
reach every healthy block in the city. If the infection cannot reach all healthy
blocks (because of empty blocks), state that as described in output section.
Sorry, some people are just out of reach! Are you ready to discover the fate
of the city? The clock is ticking!
