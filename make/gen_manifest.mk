#
# Copyright (c) 2020, Google, Inc. All rights reserved
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Generate and add constant headers, if necessary
#
# args:
# MODULE : module name (required)
# MODULE_CONSTANTS : JSON files with constants used for both the manifest and C
# 		headers (optional) (CONSTANTS is a deprecated equivalent to
# 		MODULE_CONSTANTS)
# MANIFEST : manifest for the application (optional)
#
# outputs:
# TRUSTY_APP_MANIFEST_BIN : manifest binary name, if MANIFEST
#
# If neither MODULE_CONSTANTS nor MANIFEST are set, this file does nothing.

ifneq ($(strip $(MODULE_CONSTANTS)),)
MODULE_INCLUDES += \
	$(BUILDDIR)/constants/include
endif

ifneq ($(strip $(MODULE_CONSTANTS)$(MANIFEST)),)

CONSTANTS_HEADER_DIR := $(BUILDDIR)/constants/include
MODULE_CONSTANTS_HEADERS := $(addprefix $(CONSTANTS_HEADER_DIR)/,$(MODULE_CONSTANTS_HEADERS))

ifeq ($(strip $(MANIFEST_COMPILER)),)
MANIFEST_COMPILER := trusty/user/base/tools/manifest_compiler.py
endif

# build manifest objects if manifest config json provided
# generate shared constants headers if constants provided
ifneq ($(strip $(MANIFEST)),)

TRUSTY_APP_MANIFEST_BIN := $(BUILDDIR)/$(TRUSTY_APP_NAME).manifest
$(info generating manifest for $(MODULE): $(TRUSTY_APP_MANIFEST_BIN))

$(TRUSTY_APP_MANIFEST_BIN): MANIFEST_COMPILER := $(MANIFEST_COMPILER)
$(TRUSTY_APP_MANIFEST_BIN): CONFIG_CONSTANTS := $(MODULE_CONSTANTS)
$(TRUSTY_APP_MANIFEST_BIN): HEADER_DIR := $(CONSTANTS_HEADER_DIR)
$(TRUSTY_APP_MANIFEST_BIN): $(MANIFEST) $(MANIFEST_COMPILER) $(MODULE_CONSTANTS)
	@$(MKDIR)
	@echo compiling $< to $@
	$(MANIFEST_COMPILER) -i $< -o $@ $(addprefix -c,$(CONFIG_CONSTANTS)) --header-dir $(HEADER_DIR)

else # MANIFEST is empty

# generate shared constants headers if only constants and no manifest provided
$(MODULE_CONSTANTS_HEADERS): MANIFEST_COMPILER := $(MANIFEST_COMPILER)
$(MODULE_CONSTANTS_HEADERS): CONFIG_CONSTANTS := $(MODULE_CONSTANTS)
$(MODULE_CONSTANTS_HEADERS): HEADER_DIR := $(CONSTANTS_HEADER_DIR)
$(MODULE_CONSTANTS_HEADERS): $(MANIFEST_COMPILER) $(MODULE_CONSTANTS)
	@$(MKDIR)
	@echo compiling constants for $(MODULE)
	$(MANIFEST_COMPILER) $(addprefix -c,$(CONFIG_CONSTANTS)) --header-dir $(HEADER_DIR)

endif

MODULE_SRCDEPS += $(MODULE_CONSTANTS_HEADERS)

endif # MODULE_CONSTANTS and/or MANIFEST is non-empty

CONSTANTS :=
MODULE_CONSTANTS :=
MODULE_CONSTANTS_HEADERS :=
MANIFEST :=