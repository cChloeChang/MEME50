#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/slab.h>

#define DRIVER_NAME "rc522_spi"
#define DEVICE_NAME "rfid"
#define CLASS_NAME  "rc522"

#define REG_COMMAND     0x01
#define REG_FIFO_DATA   0x09
#define REG_FIFO_LEVEL  0x0A
#define REG_BIT_FRAMING 0x0D
#define REG_TX_CONTROL  0x14
#define REG_STATUS2     0x08
#define REG_VERSION     0x37
#define CMD_IDLE        0x00
#define CMD_TRANSCEIVE  0x0C
#define CMD_AUTHENT     0x0E

static int major;
static struct class* rfid_class;
static struct device* rfid_device;
static struct spi_device* rc522_spi_dev;
static u8 last_uid[5] = {0};

static void rc522_write(u8 reg, u8 val) {
    u8 tx[2] = { (reg << 1) & 0x7E, val };
    struct spi_transfer t = { .tx_buf = tx, .len = 2 };
    spi_sync_transfer(rc522_spi_dev, &t, 1);
}

static u8 rc522_read(u8 reg) {
    u8 tx = ((reg << 1) & 0x7E) | 0x80;
    u8 rx = 0;
    struct spi_transfer t[] = {
        { .tx_buf = &tx, .len = 1 },
        { .rx_buf = &rx, .len = 1 },
    };
    spi_sync_transfer(rc522_spi_dev, t, 2);
    return rx;
}

static void rc522_antenna_on(void) {
    u8 val = rc522_read(REG_TX_CONTROL);
    if (!(val & 0x03)) {
        rc522_write(REG_TX_CONTROL, val | 0x03);
    }
}

static int rc522_request(u8 *tag_type) {
    rc522_write(REG_BIT_FRAMING, 0x07); // send only 7 bits
    rc522_write(REG_COMMAND, CMD_IDLE);
    rc522_write(REG_FIFO_DATA, 0x26); // REQA
    rc522_write(REG_COMMAND, CMD_TRANSCEIVE);
    rc522_write(REG_BIT_FRAMING, 0x87);
    msleep(10);
    
    u8 fifo_level = rc522_read(REG_FIFO_LEVEL);
    if (fifo_level >= 2) {
        tag_type[0] = rc522_read(REG_FIFO_DATA);
        tag_type[1] = rc522_read(REG_FIFO_DATA);
        return 0;
    }
    return -EIO;
}

static int rc522_anticoll(u8 *uid) {
    rc522_write(REG_BIT_FRAMING, 0x00);
    rc522_write(REG_COMMAND, CMD_IDLE);
    rc522_write(REG_FIFO_DATA, 0x93);
    rc522_write(REG_FIFO_DATA, 0x20);
    rc522_write(REG_COMMAND, CMD_TRANSCEIVE);
    rc522_write(REG_BIT_FRAMING, 0x80);
    msleep(10);

    u8 fifo_level = rc522_read(REG_FIFO_LEVEL);
    if (fifo_level >= 5) {
        for (int i = 0; i < 5; ++i) {
            uid[i] = rc522_read(REG_FIFO_DATA);
        }
        return 0;
    }
    return -EIO;
}

static ssize_t rc522_read_user(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    u8 uid[5] = {0};
    u8 atqa[2];
    if (rc522_request(atqa) == 0) {
        if (rc522_anticoll(uid) == 0) {
            if (copy_to_user(buf, uid, 5)) return -EFAULT;
            return 5;
        }
    }
    return 0;
}

static int rc522_open(struct inode *inode, struct file *file) {
    return 0;
}

static int rc522_release(struct inode *inode, struct file *file) {
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = rc522_read_user,
    .open = rc522_open,
    .release = rc522_release,
};

static int rc522_probe(struct spi_device *spi) {
    rc522_spi_dev = spi;

    rc522_write(0x01, 0x0F); // reset
    msleep(50);
    rc522_antenna_on();

    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) return major;

    rfid_class = class_create(CLASS_NAME);
    if (IS_ERR(rfid_class)) {
        unregister_chrdev(major, DEVICE_NAME);
        return PTR_ERR(rfid_class);
    }
    rfid_device = device_create(rfid_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    if (IS_ERR(rfid_device)) {
        class_destroy(rfid_class);
        unregister_chrdev(major, DEVICE_NAME);
        return PTR_ERR(rfid_device);
    }

    pr_info("RC522: initialized. Version: 0x%02x\n", rc522_read(REG_VERSION));
    return 0;
}

static void rc522_remove(struct spi_device *spi) {
    device_destroy(rfid_class, MKDEV(major, 0));
    class_destroy(rfid_class);
    unregister_chrdev(major, DEVICE_NAME);
    pr_info("RC522: removed\n");
}

static struct spi_driver rc522_driver = {
    .driver = {
        .name = DRIVER_NAME,
        .owner = THIS_MODULE,
    },
    .probe = rc522_probe,
    .remove = rc522_remove,
};

module_spi_driver(rc522_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You");
MODULE_DESCRIPTION("RC522 RFID Reader with real UID detection");
