import matplotlib.pyplot as plt

x = [*range(0,9)]
plt.xlabel('Days')

y = [99,76,1,0,0,0,0,0,0]
plt.ylabel('Number of susceptible')
plt.plot(x,y)
plt.show()

y = [1,24,96,37,3,0,0,0,0]
plt.ylabel('Number of infected')
plt.plot(x,y)
plt.show()

y = [0,0,3,63,97,100,100,100,100]
plt.ylabel('Number of recovered')
plt.plot(x,y)
plt.show()

