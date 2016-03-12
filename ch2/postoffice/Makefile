include ../../common.mk
PROJ=postoffice
COMMON_DIR=../../commons
all:$(PROJ)
$(PROJ):$(PROJ).c $(COMMON_DIR)/arr_ops.o
	$(CC) -I$(COMMON_DIR) $^ -l$(LIB_MATH) -o $@
arr_ops:arr_ops.o
arr_ops.o:$(COMMON_DIR)/arr_ops
	$(CC) -I$(COMMON_DIR) $^ -o $(COMMON_DIR)/$@
clean:
	rm -rf $(PROJ)
	rm -rf *.o