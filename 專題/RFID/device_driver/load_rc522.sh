#!/bin/bash

MODULE_NAME="rc522_kmod"
DRIVER_NAME="rc522_spi"
DEVICE_NAME="rfid"
CLASS_NAME="rc522"
DEV_PATH="/dev/$DEVICE_NAME"

echo $DRIVER_NAME | sudo tee /sys/bus/spi/devices/spi0.0/driver_override > /dev/null
echo spi0.0 | sudo tee /sys/bus/spi/drivers_probe > /dev/null

echo "[INFO] 載入 $MODULE_NAME 模組中..."

# 插入 kernel module
sudo insmod ${MODULE_NAME}.ko
if [ $? -ne 0 ]; then
    echo "[ERROR] 模組載入失敗。"
    exit 1
fi

# 取得 major number
MAJOR=$(cat /proc/devices | grep "$DEVICE_NAME" | awk '{print $1}')
if [ -z "$MAJOR" ]; then
    echo "[ERROR] 無法取得 major number，請確認模組是否正確載入。"
    exit 1
fi

# 建立裝置節點
if [ ! -e "$DEV_PATH" ]; then
    echo "[INFO] 建立裝置節點 $DEV_PATH (major=$MAJOR)..."
    sudo mknod $DEV_PATH c $MAJOR 0
    sudo chmod 666 $DEV_PATH
fi

echo "[INFO] 載入完成，裝置節點已建立於 $DEV_PATH"

