# KMeans

A windows console application to find clusters in data with any number of columns ( attributes ) using the KMeans algorithm (  https://en.wikipedia.org/wiki/K-means_clustering )

```
Usage: KMeans <data dimension> <data file path> <number of clusters>
```

The iris data set ( http://archive.ics.uci.edu/ml/datasets/Iris ) has 4 attributes

```
1. sepal length in cm 
2. sepal width in cm 
3. petal length in cm 
4. petal width in cm 
```

The application outputs

```
>KMeans.exe 4 ..\data\bezdekIris.data 3
0 5.1 3.5 1.4 0.2 , 50 7 3.2 4.7 1.4 , 100 6.3 3.3 6 2.5 , Total distance 103.982
Total distance 97.249
Total distance 97.2046

Cluster 0 means 5.006 3.428 1.462 0.246  mins: 4.3, 2.3, 1, 0.1,  maxs: 5.8, 4.4, 1.9, 0.6,  sds: 0.348947, 0.375255, 0.171919, 0.104326,

Cluster 1 means 5.90161 2.74839 4.39355 1.43387  mins: 4.9, 2, 3, 1,  maxs: 7, 3.4, 5.1, 2.4,  sds: 0.462633, 0.293885, 0.504774, 0.295091,

Cluster 2 means 6.85 3.07368 5.74211 2.07105  mins: 6.1, 2.5, 4.9, 1.4,  maxs: 7.9, 3.8, 6.9, 2.5,  sds: 0.48761, 0.28625, 0.482118, 0.276165,
```
