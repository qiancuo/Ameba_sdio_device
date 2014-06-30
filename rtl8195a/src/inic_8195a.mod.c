#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
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
	{ 0x6a91b2bc, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x69dcf2f2, __VMLINUX_SYMBOL_STR(sdio_writeb) },
	{ 0x420c86d7, __VMLINUX_SYMBOL_STR(sdio_readb) },
	{ 0x7051b3e0, __VMLINUX_SYMBOL_STR(sdio_enable_func) },
	{ 0x6cd5497e, __VMLINUX_SYMBOL_STR(sdio_writel) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
	{ 0x34ad5d1c, __VMLINUX_SYMBOL_STR(sdio_readl) },
	{ 0x648009f2, __VMLINUX_SYMBOL_STR(sdio_unregister_driver) },
	{ 0xf0fdf6cb, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xfee95de4, __VMLINUX_SYMBOL_STR(sdio_writew) },
	{ 0xae8ad9ab, __VMLINUX_SYMBOL_STR(sdio_readw) },
	{ 0x881c9e26, __VMLINUX_SYMBOL_STR(sdio_register_driver) },
	{ 0x655a8b52, __VMLINUX_SYMBOL_STR(sdio_claim_host) },
	{ 0xf60064da, __VMLINUX_SYMBOL_STR(sdio_set_block_size) },
	{ 0x4b4e68e4, __VMLINUX_SYMBOL_STR(sdio_disable_func) },
	{ 0xfefb52e5, __VMLINUX_SYMBOL_STR(sdio_release_host) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "C6A3566EE14A8FA51D0FC51");
