.PHONY: clean All

All:
	@echo "----------Building project:[ opdracht6_1 -  ]----------"
	@cd "opdracht6_1" && "$(MAKE)" -f  "opdracht6_1.mk"
clean:
	@echo "----------Cleaning project:[ opdracht6_1 -  ]----------"
	@cd "opdracht6_1" && "$(MAKE)" -f  "opdracht6_1.mk" clean
