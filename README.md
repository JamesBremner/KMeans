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
n>KMeans.exe 4 ..\data\bezdekIris.data 4
cluster 0 has 35 cluster 1 has 16 cluster 2 has 56 cluster 3 has 43 Total distance 90.4518
cluster 0 has 29 cluster 1 has 21 cluster 2 has 59 cluster 3 has 41 Total distance 84.225
cluster 0 has 28 cluster 1 has 22 cluster 2 has 59 cluster 3 has 41 Total distance 83.7341

Cluster 0 means 5.24286 3.66786 1.5  mins: 4.9, 3.3, 1.2, 0.1,  maxs: 5.8, 4.4, 1.9, 0.6,  sds: 0.236686, 0.269991, 0.148805, 0.119683,

Cluster 1 means 4.70455 3.12273 1.41364  mins: 4.3, 2.3, 1, 0.1,  maxs: 5, 3.6, 1.9, 0.3,  sds: 0.207753, 0.246672, 0.186585, 0.0522233,

Cluster 2 means 5.86102 2.73898 4.36949  mins: 4.9, 2, 3, 1,  maxs: 6.7, 3.4, 5.1, 2.4,  sds: 0.431794, 0.295168, 0.504305, 0.302313,

Cluster 3 means 6.83902 3.06341 5.67805  mins: 6.1, 2.5, 4.7, 1.4,  maxs: 7.9, 3.8, 6.9, 2.5,  sds: 0.477738, 0.282632, 0.519151, 0.313735,
```
