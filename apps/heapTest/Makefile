PROJ_WDIR=../../
CURR_DIR=$(PWD)
INCDIRS=-I $(CURR_DIR)/om/include/ -I $(PROJ_WDIR)/utils/heap/include
SRC=$(CURR_DIR)/src
BIN=$(CURR_DIR)/bin
EXEC=$(BIN)/exec

SOURCES=$(SRC)/main.cpp
OBJDIR=$(CURR_DIR)/obj

AUTODEPS:= $(patsubst $(SRC)/%.cpp,$(OBJDIR)/%.d,$(SOURCES))
OBJS=$(patsubst $(SRC)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
GCC=g++
FLAGS=-g -Wall -fPIC -gdwarf-2 -std=c++11

$(shell mkdir -p $(BIN))
$(shell mkdir -p $(OBJDIR))

all:$(EXEC)

-include $(AUTODEPS)

$(EXEC): $(OBJS)
	$(GCC) $^ -o $@ $(FLAGS) $(INCDIRS) 

$(OBJDIR)/%.o: $(SRC)/%.cpp
	$(GCC) -o $@ $(FLAGS) $(INCDIRS) -c $< 

$(OBJDIR)/%.d: $(SRC)/%.cpp
	@set -e; rm -f $@; \
         $(GCC) -MM $(INCDIRS) $(FLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,$(OBJDIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$
clean:
	rm -rf $(EXEC) $(OBJDIR)/*.d $(OBJDIR)/*.o 
