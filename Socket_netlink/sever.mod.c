#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
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

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x4cf819e6, "module_layout" },
	{ 0x676b6efd, "netlink_kernel_release" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0xb69aa266, "__netlink_kernel_create" },
	{ 0xe264d15c, "init_net" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xf112ef89, "netlink_unicast" },
	{ 0x1ecce9eb, "__nlmsg_put" },
	{ 0x3d18fb83, "__alloc_skb" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "2435A6A3ED7DCBCABD3BEA7");
