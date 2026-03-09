CC = clang
CFLAGS = -Wall -Wextra -Iinclude -D_XOPEN_SOURCE_EXTENDED -Wl,--wrap=abort
LDFLAGS = -L. -Ltesting/lib
LDLIBS = -lapp -ltesting -lmocks

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/models/circle.c $(SRC_DIR)/models/rectangle.c \
       $(SRC_DIR)/models/shape.c $(SRC_DIR)/models/triangle.c \
       $(SRC_DIR)/controller.c $(SRC_DIR)/view.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIB = build/libapp_lib.a
TARGET = build/test_model

.PHONY: all clean

all: $(TARGET)

$(TARGET): tests/main.c tests/test_model.c $(LIB)
	$(CC) $(CFLAGS) $^ -o $@ -Itesting/include $(LDFLAGS) $(LDLIBS)

$(LIB): $(OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(LIB) $(TARGET)
