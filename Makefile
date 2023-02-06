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
	@echo "-----------------------------------------------------------------------------"
	@echo "Project name : $(PROJECT_NAME)"
	@echo "Description  : $(PROJECT_DESCRIPTION)"
	@echo "License      : $(PROJECT_LICENSE)"
	@echo "Version      : $(PROJECT_VERSION)"
	@echo "Authors      : $(PROJECT_AUTHORS)"
	@echo "Last release : $(PROJECT_LAST_RELEASE)"
	@echo -e "-----------------------------------------------------------------------------\n"

depend:
ifeq ("$(wildcard $(OBJ_DIR))","")
	@mkdir $(OBJ_DIR)
endif
	@echo -n "+ generating dependencies : "
ifneq ($(strip $(SRC)),)
	@$(CXX) $(INC_DIR) -MM $(SRC:%=$(SRC_DIR)/%) \
	| sed -e 's:^[^ ]:$(OBJ_DIR)/&:' > Makefile.depend
endif
	@echo "OK"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(FILES_EXT)
	@echo -n "+ compiling $(notdir $@) : "
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INC_DIR) -c $< -o $@
	@echo "OK"

$(TARGET): $(OBJ)
	@echo -n "+ building $@ : "
	@$(CXX) $(CXXFLAGS) $(INC_DIR) $^ -o $@ $(LDFLAGS) $(LIBS)
	@echo "ok"

clean: clean_doc
	@echo -n "+ deleting binaries : "
	@\rm -rf $(OBJ_DIR) $(TARGET)
	@echo "OK"

doc:
	@$(MAKE) -C $(DOC_DIR) -s

clean_doc:
	@$(MAKE) -C $(DOC_DIR) -s clean

footer:
	@echo -e "\n-----------------------------------------------------------------------------"

include Makefile.depend

.PHONY: doc clean clean_doc
