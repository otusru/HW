#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/rbtree.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Otus");
MODULE_DESCRIPTION("Реализация rbtree в модуле ядра");

struct my_node {
    int key;
    struct rb_node rb;
};

static struct rb_root my_tree = RB_ROOT;

static int insert_node(int key)
{
    struct rb_node **new = &my_tree.rb_node, *parent = NULL;

    while (*new) {
        struct my_node *this = container_of(*new, struct my_node, rb);
        parent = *new;

        if (key < this->key)
            new = &((*new)->rb_left);
        else if (key > this->key)
            new = &((*new)->rb_right);
        else {
            printk(KERN_INFO "Ключ %d уже существует\n", key);
            return -1;
        }
    }

    struct my_node *node = kmalloc(sizeof(*node), GFP_KERNEL);
    if (!node)
        return -ENOMEM;

    node->key = key;
    rb_link_node(&node->rb, parent, new);
    rb_insert_color(&node->rb, &my_tree);

    printk(KERN_INFO "Добавлен ключ: %d\n", key);
    return 0;
}

static void traverse_tree(struct rb_root *root)
{
    struct rb_node *node;
    for (node = rb_first(root); node; node = rb_next(node)) {
        struct my_node *data = container_of(node, struct my_node, rb);
        printk(KERN_INFO "Node: %d\n", data->key);
    }
}

static void cleanup_tree(struct rb_root *root)
{
    struct rb_node *node = rb_first(root);
    while (node) {
        struct my_node *data = container_of(node, struct my_node, rb);
        node = rb_next(node);

        rb_erase(&data->rb, root);
        kfree(data);
    }
}

static int __init rbtree_module_init(void)
{
    printk(KERN_INFO "=== Загрузка модуля rbtree_example ===\n");

    insert_node(10);
    insert_node(5);
    insert_node(15);
    insert_node(7);

    printk(KERN_INFO "Обход дерева:\n");
    traverse_tree(&my_tree);

    return 0;
}

static void __exit rbtree_module_exit(void)
{
    printk(KERN_INFO "=== Выгрузка модуля rbtree_example ===\n");
    cleanup_tree(&my_tree);
}

module_init(rbtree_module_init);
module_exit(rbtree_module_exit);
