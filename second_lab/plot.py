#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import sys
import matplotlib.pyplot as plt
import numpy as np

if len(sys.argv) > 1:
    print ("Привет, {}!".format (sys.argv[1]))
    s = sys.argv[1]
print(s.split("_")[:-1])
a = np.array([float(d) for d in s.split("_")[:-1]])
x = np.linspace(0, 3, 500)
plt.plot(x, np.polyval(a, x))
plt.show()
