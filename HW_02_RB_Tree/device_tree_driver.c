#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/rbtree.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Otus");
MODULE_DESCRIPTION("Реализация устройство с использованием rbtree");

struct device_node {
    int id;
    char name[16];
    struct rb_node rb;
};

static struct rb_root device_tree = RB_ROOT;

static int add_device(int id, const char *name)
{
    struct rb_node **new = &device_tree.rb_node, *parent = NULL;

    while (*new) {
        struct device_node *this = container_of(*new, struct device_node, rb);
        parent = *new;

        if (id < this->id)
            new = &((*new)->rb_left);
        else if (id > this->id)
            new = &((*new)->rb_right);
        else {
            printk(KERN_INFO "Устройство с ID %d уже существует\n", id);
            return -1;
        }
    }

    struct device_node *dev = kmalloc(sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;

    dev->id = id;
    strncpy(dev->name, name, sizeof(dev->name) - 1);
    dev->name[sizeof(dev->name) - 1] = '\0';

    rb_link_node(&dev->rb, parent, new);
    rb_insert_color(&dev->rb, &device_tree);

    printk(KERN_INFO "Добавлено устройство: ID=%d, Name=%s\n", dev->id, dev->name);
    return 0;
}

static struct device_node *find_device(int id)
{
    struct rb_node *node = device_tree.rb_node;

    while (node) {
        struct device_node *dev = container_of(node, struct device_node, rb);

        if (id < dev->id)
            node = node->rb_left;
        else if (id > dev->id)
            node = node->rb_right;
        else
            return dev;
    }

    return NULL;
}

static void traverse_devices(void)
{
    struct rb_node *node;
    for (node = rb_first(&device_tree); node; node = rb_next(node)) {
        struct device_node *dev = container_of(node, struct device_node, rb);
        printk(KERN_INFO "Устройство: ID=%d, Name=%s\n", dev->id, dev->name);
    }
}

static void cleanup_devices(void)
{
    struct rb_node *node = rb_first(&device_tree);
    while (node) {
        struct device_node *dev = container_of(node, struct device_node, rb);
        node = rb_next(node);
        rb_erase(&dev->rb, &device_tree);
        kfree(dev);
    }
}

static int __init device_driver_init(void)
{
    printk(KERN_INFO "=== Загрузка устройства-драйвера ===\n");

    add_device(100, "devA");
    add_device(50,  "devB");
    add_device(200, "devC");

    struct device_node *dev = find_device(50);
    if (dev)
        printk(KERN_INFO "Найдено устройство: ID=%d, Name=%s\n", dev->id, dev->name);
    else
        printk(KERN_INFO "Устройство не найдено\n");

    traverse_devices();

    return 0;
}

static void __exit device_driver_exit(void)
{
    printk(KERN_INFO "=== Выгрузка устройства-драйвера ===\n");
    cleanup_devices();
}

module_init(device_driver_init);
module_exit(device_driver_exit);
