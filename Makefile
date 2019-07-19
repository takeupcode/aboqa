.PHONY: clean All

All:
	@echo "----------Building project:[ s-TUCUT - Debug ]----------"
	@cd "submodules/TUCUT" && "$(MAKE)" -f  "s-TUCUT.mk"
	@echo "----------Building project:[ aboqa - Debug ]----------"
	@"$(MAKE)" -f  "aboqa.mk"
clean:
	@echo "----------Cleaning project:[ s-TUCUT - Debug ]----------"
	@cd "submodules/TUCUT" && "$(MAKE)" -f  "s-TUCUT.mk"  clean
	@echo "----------Cleaning project:[ aboqa - Debug ]----------"
	@"$(MAKE)" -f  "aboqa.mk" clean
