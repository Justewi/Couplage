# CouplageMax

This project was made during our 4th year at Polytech' Nice Sophia for the Computability and advanced algorithmic course.
The goal is to build a random undirected graph and find the maximum matching.

Made by: [Gaspard LACROIX](https://github.com/gaspardL), [Alexis METGE](https://github.com/Hyspirit), [Liavona ZHELTANOSAVA](https://github.com/LiavonaZh)

**To compile and run the program, run the following commands:**
```
    make
    ./run.exe Type_of_graph Number_of_nodes step [min_p max_p max_thread nb_repeat -p]
```
`Type_of_graph` : g | general or b | biparti for general and bipartite graph;

`Number_of_nodes` : total number of nodes (in case of bipartite graph Number_of_nodes correspond to number of nodes of one disjoint set);

`step` : a floating value of step between probability values;

Optional options:

`min_p` and `max_p` : minimal and maximal floating values of probabilities of edge presence (the default values are 0 and 1);

`max_thread` : number of thread to run the program (the default value is 4);

`nb_repeat` : number of repetitions of running algorithm (the default value is 100);

`-p` : shows the results in the terminal while running the program.

**To compile and test the program, run the following commands:**
```
    make test
    ./test
```
