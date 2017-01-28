import sys
import matplotlib.pyplot as plt

if not len(sys.argv)==3:
    print "Need 2 arguments: xFile, yFile"
    sys.exit()

with open(sys.argv[1], 'r') as xFile:
    xVal = xFile.readlines()

with open(sys.argv[2], 'r') as yFile:
    yVal = yFile.readlines()

map(float, xVal)
map(float, yVal)

plt.subplots(figsize=(20, 10))
plt.plot(xVal, yVal, 'b.')
plt.show()
