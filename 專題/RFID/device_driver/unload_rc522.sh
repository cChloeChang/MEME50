#!/bin/bash

MODULE_NAME="rc522_kmod"
DEVICE_NAME="rfid"
DEV_PATH="/dev/$DEVICE_NAME"

echo "[INFO] 卸載 $MODULE_NAME 模組中..."

# 移除裝置節點
if [ -e "$DEV_PATH" ]; then
    echo "[INFO] 刪除裝置節點 $DEV_PATH..."
    sudo rm -f $DEV_PATH
fi

# 卸載 kernel module
sudo rmmod $MODULE_NAME
if [ $? -ne 0 ]; then
    echo "[ERROR] 模組卸載失敗。"
    exit 1
fi

echo "[INFO] 卸載完成。"

