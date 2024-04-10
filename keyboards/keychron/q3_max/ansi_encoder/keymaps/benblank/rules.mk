BOOTMAGIC_ENABLE = no
GRAVE_ESC_ENABLE = no
LTO_ENABLE = yes
MAGIC_ENABLE = no
MOUSEKEY_ENABLE = no
NKRO_ENABLE = no
SPACE_CADET_ENABLE = no

# The Q3 Max only has three available endpoints, which are normally used by the
# keyboard, the shared endpoint (for Extra Keys), and Raw HID. To free one up
# when the console is enabled, the keyboard is moved to the shared port. This
# potentially makes the keyboard unavailable while the host is booting (e.g.
# during BIOS setup).
ifeq ($(strip $(CONSOLE_ENABLE)), yes)
	KEYBOARD_SHARED_EP = yes
endif
