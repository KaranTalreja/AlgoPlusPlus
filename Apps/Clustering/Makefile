PROJ_WDIR=../../
CURR_DIR=$(PWD)
INCDIRS=-I $(CURR_DIR)/om/include/ -I $(PROJ_WDIR)/Utils/Graph/include -I $(PROJ_WDIR)/Utils/UnionFind/include -I $(PROJ_WDIR)/Utils/Heap/include
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
	@echo "$(notdir $^) --> $(notdir $@)"
	@$(GCC) $^ -o $@ $(FLAGS) $(INCDIRS) 

$(OBJDIR)/%.o: $(SRC)/%.cpp
	@echo "$(notdir $^) --> $(notdir $@)"
	@$(GCC) -o $@ $(FLAGS) $(INCDIRS) -c $< 

$(OBJDIR)/%.d: $(SRC)/%.cpp
	@echo "$(notdir $^) --> $(notdir $@)"
	@set -e; rm -f $@; \
         $(GCC) -MM $(INCDIRS) $(FLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,$(OBJDIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

test:
	@echo "Testing"
	@$(PROJ_WDIR)/Test/test.sh $(EXEC) TestCaseList

clean:
	@rm -rf $(EXEC) $(OBJDIR)/*.d* $(OBJDIR)/*.d $(OBJDIR)/*.o 

.PHONY:test
