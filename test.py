#Initialize list
listX = [1,2,3,4,5]
ListY = [7,8,9,10]
listZ = []

#Increment x
x = 0 
x = x+1

listZ = listX + ListY
print(listZ)

listZ[0] = 5
print("listZ[0]",listZ[0])
print(listZ)

x = x+1
listZ[1] = listZ[1] + x
print("listZ[1]",listZ[1])
print(listZ)


x = x+1
listZ[2] = x + listZ[2] 
print("listZ[2]",listZ[2])
print(listZ)

x = x+1
listZ[3] = listZ[3] + x
print("listZ[3]",listZ[3])
print(listZ)

if x <= 3:
  print(x)
else:
  print(listZ)