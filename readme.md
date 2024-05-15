# Reachability-Aware Fair Influence Maximization

This is the source code for a Reachability-Aware Fair Influence Maximization accepted on APWeb 2024.

## Strategies
- The simple baseline as ```greedy```
- The native Reachability UpLift method ```sRR```.
- The Reachability with tie solution Uplift+ method ```tRR```.
- The local search UpLiftX method ```lRR```.
- Two super approaches, one with naive Reachability method ```supers```, another with Tie Reachability ```supert```.

## Datasets
The dataset contains two part of graph. In the format of ```graphName_edgeDistribution``` (See detail in the Table 3 from our paper). The ```edgeDistribution``` representing for $p_{v,u}$ as the different edge probability on the graph, which containing ```xp, tp, htp, hp, idp, np```. For example the graph ```raph_spa_500_0``` with in degree distribution using dataset  ```graph_spa_500_0_idp```. 

## Run

### compile
```
g++ run.cpp -Wall -std=c++11 -O3 sfmt/SFMT.c  -o run
```


### run
Getting the results for ```uplift``` in ```graph_spa_500_0``` dataset with in degree edge distribution.

```
./run sRR 500 10000 0.02 graph_spa_500_0_idp 10000 0.1 10 lt 
```

