.PHONY: clean All

All:
	@echo "----------Building project:[ DrawingInterface - Debug ]----------"
	@cd "DrawingInterface" && "$(MAKE)" -f  "DrawingInterface.mk"
clean:
	@echo "----------Cleaning project:[ DrawingInterface - Debug ]----------"
	@cd "DrawingInterface" && "$(MAKE)" -f  "DrawingInterface.mk" clean
