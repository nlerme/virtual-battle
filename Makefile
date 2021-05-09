# Variables
include Makefile.common
CXX       = g++
CXXFLAGS  = -O3 -Wall -g
LDFLAGS   = -L/usr/lib
INC_DIR   = -Iinclude -I/usr/include/freetype2
LIBS      = -lm -lSDL -lGL -lGLEW -lfreetype -lGLU
DOC_DIR   = doc
SRC_DIR   = src
OBJ_DIR   = obj
FILES_EXT = cpp
TARGET    = main
SRC       = $(notdir $(wildcard $(SRC_DIR)/*.$(FILES_EXT)))
OBJ       = $(SRC:%.$(FILES_EXT)=$(OBJ_DIR)/%.o)

# Rules
all: header depend $(OBJ) $(TARGET) footer

header:
	@echo -e "-----------------------------------------------------------------------------"
	@echo -e "$(PROJECT_NAME) v$(PROJECT_VERSION) - $(PROJECT_DESCRIPTION)"
	@echo -e "Authors: $(PROJECT_AUTHORS)"
	@echo -e "Last release: $(PROJECT_LAST_RELEASE)"
	@echo -e "-----------------------------------------------------------------------------\n"

depend:
	@echo -n "+ generating dependencies : "
ifneq ($(strip $(SRC)),)
	@$(CXX) $(INC_DIR) -MM $(SRC:%=$(SRC_DIR)/%) \
	| sed -e 's:^[^ ]:$(OBJ_DIR)/&:' > Makefile.depend
endif
	@echo "ok"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(FILES_EXT)
	@echo -n "+ compiling $(notdir $@) : "
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INC_DIR) -c $< -o $@
	@echo "ok"

$(TARGET): $(OBJ)
	@echo -n "+ building $@ : "
	@$(CXX) $(CXXFLAGS) $(INC_DIR) $^ -o $@ $(LDFLAGS) $(LIBS)
	@echo "ok"

clean: clean_doc
	@echo -n "+ deleting binaries : "
	@rm -f $(OBJ_DIR)/*.o $(TARGET)
	@echo "ok"

doc:
	@$(MAKE) -C $(DOC_DIR) -s

clean_doc:
	@$(MAKE) -C $(DOC_DIR) -s clean

footer:
	@echo -e "\n-----------------------------------------------------------------------------"

include Makefile.depend

.PHONY: doc clean clean_doc
