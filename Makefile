.PHONY: clean All

All:
	@echo "----------Building project:[ opdracht17_3 -  ]----------"
	@cd "opdracht17_3" && "$(MAKE)" -f  "opdracht17_3.mk"
clean:
	@echo "----------Cleaning project:[ opdracht17_3 -  ]----------"
	@cd "opdracht17_3" && "$(MAKE)" -f  "opdracht17_3.mk" clean
