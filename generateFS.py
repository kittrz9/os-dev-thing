import os
import struct

# https://wiki.osdev.org/SFS

blockSize = 2 # 512 bytes
blockSizeBytes = 512 #2**(blockSize + 7)

totalBlocks = 0x100
fsSize = blockSizeBytes * totalBlocks

includedFiles = [
	"build/kernel.bin",
	"TODO.md"
]

for f in os.listdir("build/programs/"):
	if f.endswith(".elf"):
		includedFiles.append("build/programs/" + f)

#for i, f in enumerate(includedFiles):
	#includedFiles[i] = os.path.basename(f)
print(includedFiles)

indices = [ (0x02, 0) ] # starting marker entry

fs = bytearray(fsSize)

currentBlock = 0
for filename in includedFiles:
	with open(filename, "rb") as f:
		data = f.read(-1)
		blocks = len(data)//blockSizeBytes
		entry = (
			0x12, # file entry id
			0, # number of continuation entries
			0, # timestamp
			currentBlock + 1, # starting block
			currentBlock + 2 + blocks, # endingBlock
			len(data), # file size
			os.path.basename(filename), # file name
		)
		indices.append(entry)
		for i, b in enumerate(data):
			fs[int(currentBlock*blockSizeBytes) + i] = b
		currentBlock += blocks + 1

indices.append( (
	0x01, # volume identifier
	0, # timestamp
	"asdf", # volume name
))

indicesIndex = fsSize-64
for e in indices:
	fs[indicesIndex + 0] = e[0]
	if e[0] == 0x12:
		fs[indicesIndex + 1] = e[1]
		for i, b in enumerate(struct.pack("<Q", e[2])):
			fs[indicesIndex + 2 + i] = b
		for i, b in enumerate(struct.pack("<Q", e[3])):
			fs[indicesIndex + 0xa + i] = b
		for i, b in enumerate(struct.pack("<Q", e[4])):
			fs[indicesIndex + 0x12 + i] = b
		for i, b in enumerate(struct.pack("<Q", e[5])):
			fs[indicesIndex + 0x1a + i] = b
		for i, b in enumerate(e[6]):
			fs[indicesIndex + 0x22 + i] = ord(b)
	elif e[0] == 0x1:
		for i, b in enumerate(struct.pack("<Q", e[1])):
			fs[indicesIndex + 4 + i] = b
		for i, b in enumerate(e[2]):
			fs[indicesIndex + 0xc + i] = ord(b)
	indicesIndex -= 64

dataBlocks = currentBlock
# probably a bit dumb to use this format since it has a ton of space reserved for boot code that I'm just not gonna bother with and just have my own boot code elsewhere lmao
superblock = bytearray(bytes(0x200))

# sfs magic number
superblock[0x1ac] = 0x53
superblock[0x1ad] = 0x46
superblock[0x1ae] = 0x53

# sfs version
superblock[0x1af] = 0x10

# block size
superblock[0x1bc] = blockSize

# data area size
for i, b in enumerate(struct.pack("<Q", dataBlocks)):
	superblock[0x19c + i] = b

# total blocks
for i, b in enumerate(struct.pack("<Q", totalBlocks + 1)): # accounting for the superblock
	superblock[0x1b0 + i] = b

# checksum
checksum = 0
for x in superblock[0x1ac:0x1bd]:
	checksum += x
checksum &= 0xff
superblock[0x1bd] = (0x100 - checksum)&0xff


with open("build/fs.bin", "wb") as f:
	f.write(superblock)
	f.write(fs)
