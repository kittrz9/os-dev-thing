#!/bin/env python

# converts a grayscale image to an array of values
# mainly made so I can create a simple font for text rendering later
# probably should be converted to pack the pixels into single bits to save on space
# but this works for now

import sys
import os
from PIL import Image



def main():
	if len(sys.argv) != 2:
		exit(1)

	file = sys.argv[1]

	if not os.path.exists(file):
		return 1

	name = os.path.splitext(file)[0]

	img = Image.open(file);
	pixels = img.load();

	print(f"/* {sys.argv} */")

	print("#include <stdint.h>")


	print(f"uint16_t {name}W = {img.size[0]};")
	print(f"uint16_t {name}H = {img.size[1]};")


	print(f"static const uint8_t {name}[] = {{", end='')
	for y in range(img.size[1]):
		#print("\t", end='')
		asdf = 0
		for x in range(8):
			#print(str(pixels[x,y][0]) + ",", end='')
			if pixels[x,y][0] > 0: asdf |= (1<<(7-x))
			#asdf <<= 1
		print(f"{asdf},", end='')

	print("};")

	return 0

if __name__ == "__main__":
	exit(main())
