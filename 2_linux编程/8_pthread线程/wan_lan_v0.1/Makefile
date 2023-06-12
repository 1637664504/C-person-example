##############################################
#
# OpenWrt Makefile for libjrd-status-info
#
##############################################
include $(TOPDIR)/rules.mk

PKG_NAME := wan_lan
PKG_VERSION := 0.1
PKG_RELEASE := 1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
TARGET_CFLAGS += -ggdb3

define Package/$(PKG_NAME)
	SECTION:=oem
	CATEGORY:=OEM
	TITLE:=library-- $(PKG_NAME)
	DEPENDS:=+common
endef

define Package/$(PKG_NAME)/description
	Getting and Setting AP/Modem info.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Configure
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_BUILD_DIR)/wan_lan $(1)/usr/bin/
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_BUILD_DIR)/wan_lan $(1)/usr/bin/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
