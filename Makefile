.PHONY: clean All

All:
	@echo "----------Building project:[ opdracht17_1 -  ]----------"
	@cd "opdracht17_1" && "$(MAKE)" -f  "opdracht17_1.mk"
clean:
	@echo "----------Cleaning project:[ opdracht17_1 -  ]----------"
	@cd "opdracht17_1" && "$(MAKE)" -f  "opdracht17_1.mk" clean
