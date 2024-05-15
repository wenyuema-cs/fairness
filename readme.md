# Reachability-Aware Fair Influence Maximization

This is the source code for a Reachability-Aware Fair Influence Maximization

## Dataset
The dataset contains two part of graph. In the format of ```graphName_edgeDistribution``` (See detail in the Table 3 from our paper). The ```edgeDistribution``` representing for $p_{v,u}$ as the different edge probability on the graph, which containing ```xp, tp, htp, hp, idp, np```. For example the graph ```raph_spa_500_0``` with in degree probability using dataset  ```graph_spa_500_0_idp```. 

## Run

### compile
```
g++ run.cpp -Wall -std=c++11 -O3 sfmt/SFMT.c  -o run
```


### run
```
./run sRR 500 10000 0.02 graph_spa_500_0_idp 10000 0.1 10 lt 
```

