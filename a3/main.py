import math

theta = math.pi

x = int(input("x: "))
y = int(input("y: "))

print("new x: " + str(int(x* math.cos(theta) - y * math.sin(theta))))
print("new y: " + str(int(x* math.sin(theta) + y * math.cos(theta))))