#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe8213e80, "_printk" },
	{ 0xc2f71d5e, "proc_create" },
	{ 0x5aec4bc0, "proc_remove" },
	{ 0x5cb46e6d, "validate_usercopy_range" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0xaa47b76e, "__arch_copy_to_user" },
	{ 0x9c4ed43a, "alt_cb_patch_nops" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0xc7ea9460, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xe8213e80,
	0xc2f71d5e,
	0x5aec4bc0,
	0x5cb46e6d,
	0xa61fd7aa,
	0xaa47b76e,
	0x9c4ed43a,
	0xd272d446,
	0xc7ea9460,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"_printk\0"
	"proc_create\0"
	"proc_remove\0"
	"validate_usercopy_range\0"
	"__check_object_size\0"
	"__arch_copy_to_user\0"
	"alt_cb_patch_nops\0"
	"__stack_chk_fail\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "963F94AFFA7E7353E1DADEB");
