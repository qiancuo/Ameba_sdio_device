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
	{ 0x4d5503c4, "module_layout" },
	{ 0xdc775fbf, "sdio_readb" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xcb46cbe9, "sdio_enable_func" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0x6f2a5dbf, "sdio_unregister_driver" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xc5a07d83, "sdio_register_driver" },
	{ 0xc218942d, "sdio_memcpy_fromio" },
	{ 0x4aa31d0, "sdio_claim_host" },
	{ 0x1d5820a2, "sdio_set_block_size" },
	{ 0xb1dc4987, "sdio_disable_func" },
	{ 0xee761027, "sdio_release_host" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "DEC8D5B5D1FB78B512D7895");
