i=8

def printer():
    i = 5
    print("inside fun = ",i)

a= [2,3,4]
# Fix this list below, it shows as [2,3,4,4]
# a= [2,3,4,]

print("list = ",a)
printer()
print("outside fun = ",i)
printer()