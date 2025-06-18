#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

#define MODULE_NAME "hello_module"
#define MAX_LEN 128

MODULE_LICENSE("GPL");
MODULE_AUTHOR("otus");
MODULE_DESCRIPTION("Hello, World!");

#define pr_fmt(fmt) MODULE_NAME ": " fmt

static char str_buf[MAX_LEN] = {0};
static int idx = 0;
static char ch_val = ' ';

static int param_set_idx(const char *val, const struct kernel_param *kp)
{
    int temp;
    if (kstrtoint(val, 10, &temp))
        return -EINVAL;

    if (temp < 0 || temp >= MAX_LEN)
        return -EINVAL;

    idx = temp;
    return 0;
}

static int param_get_idx(char *buffer, const struct kernel_param *kp)
{
    return sprintf(buffer, "%d", idx);
}

static const struct kernel_param_ops param_ops_idx = {
    .set = param_set_idx,
    .get = param_get_idx,
};

module_param_cb(idx, &param_ops_idx, &idx, 0660);
MODULE_PARM_DESC(idx, "Индекс позиции в строковом буфере");

static int param_set_ch_val(const char *val, const struct kernel_param *kp)
{
    char c = val[0];

    if (c < 32 || c > 126)
        return -EINVAL;

    ch_val = c;
    str_buf[idx] = c;
    return 0;
}

static int param_get_ch_val(char *buffer, const struct kernel_param *kp)
{
    return sprintf(buffer, "%c", ch_val);
}

static const struct kernel_param_ops param_ops_ch_val = {
    .set = param_set_ch_val,
    .get = param_get_ch_val,
};

module_param_cb(ch_val, &param_ops_ch_val, &ch_val, 0660);
MODULE_PARM_DESC(ch_val, "ASCII-символ для вставки в строку");

static int param_get_str_buf(char *buffer, const struct kernel_param *kp)
{
    return scnprintf(buffer, MAX_LEN, "%s", str_buf);
}

static const struct kernel_param_ops param_ops_str_buf = {
    .set = NULL,
    .get = param_get_str_buf,
};

module_param_cb(str_buf, &param_ops_str_buf, &str_buf, 0444);
MODULE_PARM_DESC(str_buf, "Строковый буфер (только для чтения)");

static int __init hello_init(void)
{
    pr_info("Модуль загружен\n");
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Модуль выгружен\n");
}

module_init(hello_init);
module_exit(hello_exit);
