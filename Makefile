.PHONY: clean All

All:
	@echo "----------Building project:[ opdracht13_3 -  ]----------"
	@cd "opdracht13_3" && "$(MAKE)" -f  "opdracht13_3.mk"
clean:
	@echo "----------Cleaning project:[ opdracht13_3 -  ]----------"
	@cd "opdracht13_3" && "$(MAKE)" -f  "opdracht13_3.mk" clean
