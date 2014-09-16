LDFLAGS += -lpthread -lrt -ljsmn
CFLAGS  += -fPIC -fno-builtin-memcmp
include main.mk
