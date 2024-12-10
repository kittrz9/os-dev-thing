#!/bin/sh

set -xe

ORIGIN_DIR="$(readlink -f "$(dirname "$0")")"
export ORIGIN_DIR

# I don't think you can use the source command in posix sh
# so I gotta use this instead
# https://stackoverflow.com/questions/11588583/is-the-shells-source-posix-standard
. ./getTools.sh

cd "$ORIGIN_DIR"

if [ -z "$(command -v "$LD")" ]; then
	echo "cross compiler not found"
	exit 1
fi

CFLAGS="$CFLAGS -g -O2 -Wall -Wextra -Wpedantic -std=gnu99 -ffreestanding -fno-builtin -fPIE -march=i686"
LDFLAGS="$LDFLAGS -O2 -nostdlib -static --no-dynamic-linker -z max-page-size=0x1000"
INCLUDES="$INCLUDES -Isrc/common"
DEFINES="$DEFINES "

rm -rf build/ obj/
mkdir -p build/ obj/

OBJS=""

. ./src/common/build.sh

. ./src/stage2/build.sh

. ./src/kernel/build.sh

. ./src/programs/build.sh

# incredibly jank solution to getting the stage2 size into boot.asm lmao
# also now requires stage2 to be built before boot.asm but whatever
STAGE2_SIZE="$(python -c "import os; import math; a=os.path.getsize(\"build/stage2.bin\");print(math.ceil(a/512))")"
STAGE2_SIZE_BYTES="$(echo "$STAGE2_SIZE * 512" | bc)"
truncate build/stage2.bin -s $STAGE2_SIZE_BYTES

# moving this temporarily so it doesn't put the build directory in the tar file
mv build/kernel.bin ./

# eventually make this its own folder with stuff in it
tar -cvf build/fs.tar TODO.md kernel.bin -b 1
cd "$ORIGIN_DIR"/build/programs
tar -rf "$ORIGIN_DIR"/build/fs.tar *.elf
cd "$ORIGIN_DIR"
FS_SIZE="$(python -c "import os; import math; a=os.path.getsize(\"build/fs.tar\");print(math.ceil(a/512))")"
FS_SIZE_BYTES="$(echo "$FS_SIZE * 512" | bc)"

mv kernel.bin build/

nasm -fbin src/boot.asm -dfssize=$FS_SIZE -dstage2size=$STAGE2_SIZE -o build/boot.bin

# combine bootsector and stage2
#cat build/boot.bin build/stage2.bin build/fs.tar > build/os.bin

# create os disk image
# essentially does the same thing it used to do when it just merged everything together
# but now the partition table actually makes sense
# and it'll probably be easier to get an actual filesystem working
STAGE2_END_SECTOR="$(echo "$STAGE2_SIZE + 1" | bc)"
FS_START_SECTOR="$(echo "$STAGE2_END_SECTOR + 1" | bc)"
FS_END_SECTOR="$(echo "$STAGE2_END_SECTOR + $FS_SIZE" | bc)"
dd if=/dev/zero of=build/os.bin bs=1M count=1
parted -s build/os.bin mklabel msdos mkpart primary 1S "${STAGE2_END_SECTOR}S" mkpart primary "${FS_START_SECTOR}S" "${FS_END_SECTOR}S"
dd if=build/boot.bin of=build/os.bin conv=notrunc bs=1 count=446
dd if=build/stage2.bin of=build/os.bin conv=notrunc seek=512 bs=1 count=$STAGE2_SIZE_BYTES
dd if=build/fs.tar of=build/os.bin conv=notrunc seek="$(echo "512 + $STAGE2_SIZE_BYTES" | bc)" bs=1 count=$FS_SIZE_BYTES

