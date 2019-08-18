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
KMeans.exe 4 ..\data\bezdekIris.data 3
cluster 0 has 53 cluster 1 has 60 cluster 2 has 37 Total distance 97.6933
cluster 0 has 51 cluster 1 has 61 cluster 2 has 38 Total distance 90.5021
cluster 0 has 50 cluster 1 has 61 cluster 2 has 39 Total distance 90.2438
cluster 0 has 50 cluster 1 has 60 cluster 2 has 40 Total distance 90.1218
```
