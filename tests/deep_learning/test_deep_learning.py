import numpy as np

def sigmoid(x):
  return 1 / (1 + np.exp(-x))

def dfsigmoid(x):
  return x * (1 - x)
    
inputs = np.array([
  [0, 0, 1],
  [0, 1, 1],
  [1, 0, 1],
  [1, 1, 1]
])
    
outputs = np.array([
  [0, 
   0,
   1,
   1]
]).T

# seed random numbers to make calculation
# deterministic (just a good practice)
np.random.seed(1)

# initialize weights randomly with mean 0
weights = 2 * np.random.random((3, 1)) - 1

for iter in xrange(10000):
    # forward propagation
    layer = sigmoid(np.dot(inputs, weights))

    errors = (outputs - layer)
    slopes = dfsigmoid(layer)

    # adjust weights using error and slope
    weights += np.dot(inputs.T, errors * slopes)

print "Output After Training:"
#print str(layer[0]), layer[1], layer[2], layer[3]
print(" ".join(str(*x) for x in layer))
