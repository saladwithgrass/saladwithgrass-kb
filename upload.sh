#!/usr/bin/bash
DEVICE=$1
FILE=$2
PICO_MOUNT_DIR=/mnt/pico/

ABORT_WITH_ERRORS=false

if [[ -z "$DEVICE" ]]; then 
    echo "ERROR: RPi Pico device must be defined."
    ABORT_WITH_ERRORS=true
fi

if [[ -z "$FILE"  ]]; then
    echo "ERROR: File to upload must be defined."
    ABORT_WITH_ERRORS=true
fi

if [[ ! $FILE == *.uf2 ]]; then
    echo "ERROR: FILE MUST HAVE .uf2 extension."
    ABORT_WITH_ERRORS=true
fi

if $ABORT_WITH_ERRORS; then 
    echo "Aborting with errors."
    exit 1
fi

sudo mount $DEVICE $PICO_MOUNT_DIR
sudo cp $FILE $PICO_MOUNT_DIR
sudo sync
sudo umount $PICO_MOUNT_DIR
