#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MAJOR_NUM 666
#define MODULE_NAME "final"

static int iCount = 0;
static char userChar[100];

struct file *file_open(const char *path, int flags, int rights);
void file_close(struct file *file);
int file_read(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size);
int file_write(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size);

static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos)
{
    printk("Read: Enter Read function\n");
    __copy_from_user(userChar, buf, count);
    userChar[count - 1] = 0;

    char gpio[4];
    strncpy(gpio, userChar, 3);
    gpio[3] = 0;

    // value path
    char gpioValuePath[64];
    snprintf(gpioValuePath, sizeof(gpioValuePath), "/sys/class/gpio/gpio%s/value", gpio);
    gpioValuePath[63] = 0;

    struct file *io;
    io = file_open(gpioValuePath, O_RDONLY, 0);
    file_read(io, 0, userChar, 2);
    file_close(io);

    __copy_to_user(buf, userChar, count);

    return 0;
}

static ssize_t drv_write(struct file *filp, const char *buf, size_t count, loff_t *ppos)
{
    printk("Write: Enter Write function\n");
    __copy_from_user(userChar, buf, count);
    userChar[count - 1] = 0;
    printk(userChar);

    char gpio[4];
    strncpy(gpio, userChar, 3);
    gpio[3] = 0;
    // printk(gpio);

    // export gpio
    char exportPath[64] = "/sys/class/gpio/export";

    struct file *io;
    io = file_open(exportPath, O_WRONLY, 0);
    file_write(io, 0, gpio, 4);
    file_close(io);

    // gpio direction
    char gpioDirectionPath[64];
    snprintf(gpioDirectionPath, sizeof(gpioDirectionPath), "/sys/class/gpio/gpio%s/direction", gpio);
    gpioDirectionPath[63] = 0;

    struct file *io1;
    io1 = file_open(gpioDirectionPath, O_WRONLY, 0);
    file_write(io1, 0, "out\0", 4);
    file_close(io1);

    // set value
    char value[2];
    value[0] = userChar[3];
    value[1] = 0;
    // printk(value);

    char gpioValuePath[64];
    snprintf(gpioValuePath, sizeof(gpioValuePath), "/sys/class/gpio/gpio%s/value", gpio);
    gpioValuePath[63] = 0;

    struct file *io2;
    io2 = file_open(gpioValuePath, O_WRONLY, 0);
    file_write(io2, 0, value, 2);
    file_close(io2);
    // printk("set valueiacorrectidia");

    // iCount++;
    return count;
}

long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk("I/O Control: Enter I/O Control function\n");
    return 0;
}

static int drv_open(struct inode *inode, struct file *filp)
{
    printk("Open: Enter Open function\n");
    return 0;
}

static int drv_release(struct inode *inode, struct file *filp)
{
    printk("Release: Enter Release function\n");
    return 0;
}

struct file_operations drv_fops =
    {
        read : drv_read,
        write : drv_write,
        unlocked_ioctl : drv_ioctl,
        open : drv_open,
        release : drv_release,
    };

static int final_init(void)
{
    if (register_chrdev(MAJOR_NUM, MODULE_NAME, &drv_fops) < 0)
    {
        printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
        return (-EBUSY);
    }

    printk("<1>%s: started\n", MODULE_NAME);
    return 0;
}

static void final_exit(void)
{
    unregister_chrdev(MAJOR_NUM, MODULE_NAME);
    printk("<1>%s: removed\n", MODULE_NAME);
}

module_init(final_init);
module_exit(final_exit);

struct file *file_open(const char *path, int flags, int rights)
{
    struct file *filp = NULL;
    mm_segment_t oldfs;
    int err = 0;

    oldfs = get_fs();
    set_fs(get_ds());
    filp = filp_open(path, flags, rights);
    set_fs(oldfs);
    if (IS_ERR(filp))
    {
        err = PTR_ERR(filp);
        return NULL;
    }
    return filp;
}

void file_close(struct file *file)
{
    filp_close(file, NULL);
}

int file_read(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size)
{
    mm_segment_t oldfs;
    int ret;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_read(file, data, size, &offset);

    set_fs(oldfs);
    return ret;
}

int file_write(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size)
{
    mm_segment_t oldfs;
    int ret;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_write(file, data, size, &offset);

    set_fs(oldfs);
    return ret;
}
