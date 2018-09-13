
CFLAGS += -DDEBUG
LFLAGS += 
SRC = $(wildcard *.cpp)
HDR = $(wildcard *.hpp) $(wildcard *.h)
OBJ = $(subst .cpp,.o,$(SRC))
GCC = g++
TARGET = hammingTest

.PHONY: clean run

$(TARGET) : $(OBJ)
	$(GCC) -o $@ $(LFLAGS) $<

test: $(TARGET)
	@echo "Expect 0 result, no errors:"
	./$(TARGET) 0 0 0 0 0 0 0 0 0 0 0 0
	@echo -e "\nExpect 10 result, no errors:"
	./$(TARGET) 0 1 0 0 1 0 1 0 0 0 0 0 
	@echo -e "\nExpect 10 result, fixed error:"
	./$(TARGET) 0 1 0 0 1 0 1 0 0 1 0 0 
	@echo -e "\nExpect error:"
	./$(TARGET) 0 1 0 1 1 0 1 0 0 1 0 0 

%.o : %.cpp
	$(GCC) -c -o $@ $(CFLAGS) $<

clean:
	rm -f $(OBJ) $(TARGET)


