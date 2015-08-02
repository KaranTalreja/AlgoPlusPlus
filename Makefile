doc:
	rm -rf doc 
	doxygen DoxyGen.config 2>.err 

.PHONY: doc
