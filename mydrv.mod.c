#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xc6c01fa, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x8ab0c78c, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xbf7ea475, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x67e6ac0a, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x81fcd7c8, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x92a94ad2, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x34e5b11, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x1423ef8b, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0xe2d432f9, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x5b1b1532, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "91BFC00A603C22327DFF4F3");
