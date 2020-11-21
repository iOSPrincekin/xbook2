#include <xbook/fs.h>
#include <xbook/diskman.h>
#include <xbook/debug.h>
#include <fsal/fsal.h>
#include <fsal/fstype.h>
#include <stddef.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/ioctl.h>

int file_system_init()
{
    printk(KERN_INFO "fs: init start.\n");
    if (disk_manager_init() < 0)
        panic("fs: init disk manager failed!\n");

<<<<<<< HEAD
    /* 初始化接口部分 */
    if (init_fstype() < 0) {
        panic("init fstype failed, service stopped!\n");
    }
    
    /* 初始化文件系统抽象层 */
    if (init_fsal() < 0) {
        panic("init fsal failed, service stopped!\n");
    }
    printk("[fs]: init done.\n");
    
    // open sbin/desktop
#if 0
    int fd = sys_open("/sbin/desktop", O_RDONLY);
    if (fd < 0) {
        printk("open fd failed!\n");
        return -1;
    }
    uint32_t *buf = mem_alloc(PAGE_SIZE * 100);
    size_t need = PAGE_SIZE * 100;
    sys_lseek(fd, 0, SEEK_SET);
    int rd = sys_read(fd, buf, need);
    printk("need: %d, read: %d\n", need, rd);
    #if 0
    int i;
    for (i = 0; i <  512*15 / 4; i++) {
        printk(" %8x ", buf[i]);
    }
    #endif
    spin("test");
#endif
#if 0
    /* test */
    int fd = sys_open("/root/kfs", O_CREAT | O_RDWR);
    if (fd < 0)
        return -1;
=======
    if (fstype_init() < 0)
        panic("fs: init fstype failed, service stopped!\n");
>>>>>>> purekern
    
    if (fsal_init() < 0) {
        panic("fs: init fsal failed, service stopped!\n");
    }
    printk(KERN_INFO "fs: init done.\n");
    return 0;
}
