.PHONY: clean All

All:
	@echo "----------Building project:[ opdracht6_2 -  ]----------"
	@cd "opdracht6_2" && "$(MAKE)" -f  "opdracht6_2.mk"
clean:
	@echo "----------Cleaning project:[ opdracht6_2 -  ]----------"
	@cd "opdracht6_2" && "$(MAKE)" -f  "opdracht6_2.mk" clean
