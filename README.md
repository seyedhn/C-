This repository contains the C++ codes for my final year BSc project. The main objective of the project was to model forest fires, specifically the critical forest density. Other factors such as lightning, rain, wind and tree growth rate were also considered.

The forest model is an example of percolation, a geometrical phase transition. The percolation threshold, or in this case the critical forest density p_c, is a special number. Imagine an N by N grid which we fill it by trees with a probability p, the forest density. We define a cluster as all the occupied sites which are connected together. If the largest cluster in the grid extends from one edge to the other edge of the grid, we call it a percolating cluster. It turns out that for values of p < p_c, the probability of finding a percolating cluster is vanishingly small, whereas for p > p_c, the probability is almost unity. At p_c, the system becomes scale invariant. In the forest fire model, p_c corresponds to the density which takes the most time for the fire to stop.

Thus, p_c can be found in two ways. 
1.	Finding the largest cluster for a range of forest densities. At p_c, the largest cluster size is abruptly changed.
2.	For a variety of forest densities, let the forest burn and measure the time until fire stops. The longest time corresponds to p_c.

C++ was used to find p_c using both methods. The grid was defined as an integer double array and filled with trees (Grid[i][j] = 1) with probability p. Empty slots were set to 0. The largest cluster was found by picking up trees and counting all the consecutive adjacent trees. The fire spread was done in time steps. At first, the forest was ignited. Then at each subsequent time step, a tree with a neighboring fire would turn into fire (Grid[i][j] = 2) and the fire would go empty (Grid[i][j] = 0). When there is no remaining fire, the simulation stops and the time steps were counted. The results were exported into Excel and plotted.

It was found that without external factors, p_c = 40%. A higher strike and tree growth rate significantly decreases p_c, whereas rain slightly increases this value. Wind has no effect. It was also found that for p << p_c, largest cluster size scales as Log(N), whereas for p >> p_c, it scales as N^2. 

