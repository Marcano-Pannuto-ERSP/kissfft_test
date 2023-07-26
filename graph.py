import matplotlib.pyplot as plt
import struct

# unpack doubles from amplitude file
amp_file = open("amplitudes", "rb")
lines = amp_file.readlines()
all_bytes = bytearray()
for line in lines:
    all_bytes += bytes(line)
# print(all_bytes)
data = struct.iter_unpack("<d", all_bytes)

y = []

for d in data:
    y.append(d[0])

print(len(y))

N = 40960 / 2
num_doubles = int(81928 / 8) # size of amplitudes file / 8 = num doubles in file
x = [(7813/N) * i for i in range(num_doubles)]

# plt.hist(y, bins=1)
# plt.scatter(x,y)
plt.plot(x,y)
plt.show()

# print ([int(i) for i in x])
