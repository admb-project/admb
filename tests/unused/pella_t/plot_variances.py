import sys
import fileinput
import copy
from contextlib import closing
import matplotlib.pyplot as plt
import numpy as np
import json

def get_data(inputs):
  matrix = []
  with closing(fileinput.input(files = inputs)) as f:
    lst = []
    for line in f:
      if (len(line) > 0):
        if (line.startswith("# Number of parameters =")):
          if (len(lst) > 0):
            matrix.append(copy.copy(lst))
            del lst[:]
            lst = []
          s = line.split()
          lst.append(float(s[10]))
          lst.append(float(s[15]))
        elif (line[0] != '#'):
          lst.extend([float(x) for x in line.split()])
    matrix.append(copy.copy(lst))

  return np.transpose(matrix)

def compute_means(data):
  means = []
  for row in data:
    means.append(np.mean(row))
  return means

def compute_variances(data):
  variances = []
  for row in data:
    variances.append(np.var(row))
  return variances

def write_report(data, means, variances):
  print "Min,Max,Mean,Variance" 
  for i in range(0, len(data)):
    print '{0},{1},{2},{3}'.format(min(data[i]), max(data[i]), means[i], variances[i])

def plot(data, means, variances):
  fig = plt.figure()
  lower = []
  upper = []
  for i in range(0, len(means)):
    upper.append(max(data[i]) - means[i])
    lower.append(means[i] - min(data[i]))
  lengths = []
  lengths.append(lower);
  lengths.append(upper);
  plt.errorbar(range(0, len(means)), means, yerr=lengths, marker="o", sketch_params=float)
  for i in range(0, len(means)):
    for d in data[i]:
      plt.scatter(i, d, c="k", marker=".")
  plt.show()

if __name__ == "__main__":
  data = get_data(sys.argv[1:])
  means = compute_means(data)
  variances = compute_variances(data)
  write_report(data, means, variances)
  plot(data, means, variances)
