# Variables
DOXYGEN_FILE = doc.doxygen
DOCS_DIRS    = `find . -maxdepth 1 -type d -printf "%f " | cut -d' ' -f2- -`

# Core
all:
	@echo -n "+ generating doc : "
	@doxygen $(DOXYGEN_FILE) &>/dev/null
	@echo "OK"

clean:
	@echo -n "+ deleting doc : "
	@for Dir in $(DOCS_DIRS); do \
		\rm -rf $$Dir/*; \
	done
	@echo "OK"

footer:

.PHONY: all clean
