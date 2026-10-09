RACK_DIR ?= ../..


SOURCES = $(wildcard src/*.cpp) $(wildcard src/*.c)

# Build both third-party libraries from pinned source revisions into a
# per-target prefix. The plugin never links against system copies.
DEPS_ARCH ?= $(ARCH_NAME)
DEPS_PREFIX = build/deps/$(DEPS_ARCH)/prefix
DEPS_STAMP = build/deps/$(DEPS_ARCH)/.built
STK_LIB = $(DEPS_PREFIX)/lib/libstk.a
GAMMA_LIB = $(DEPS_PREFIX)/lib/libGamma.a

FLAGS += -I$(DEPS_PREFIX)/include
CXXFLAGS += -Wno-cpp
LDFLAGS += $(STK_LIB) $(GAMMA_LIB)


DISTRIBUTABLES += $(wildcard LICENSE*) res
# Must include the VCV plugin Makefile framework
include $(RACK_DIR)/plugin.mk

$(DEPS_STAMP): scripts/build-dependencies.sh
	@mkdir -p $(@D)
	CC="$(CC)" CXX="$(CXX)" AR="$(AR)" RANLIB="$(RANLIB)" \
	CROSS_COMPILE="$(CROSS_COMPILE)" MACHINE="$(MACHINE)" \
	./scripts/build-dependencies.sh "$(DEPS_ARCH)" "$(DEPS_PREFIX)"

# Dependency headers must exist before any plugin translation unit is compiled.
$(OBJECTS): $(DEPS_STAMP)

.PHONY: audit-deps
audit-deps: $(DEPS_STAMP)
	@./scripts/audit-static-libraries.sh "$(DEPS_ARCH)" "$(DEPS_PREFIX)"

