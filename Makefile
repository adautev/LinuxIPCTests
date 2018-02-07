.PHONY: clean All

All:
	@echo "----------Building project:[ POSIXThreading - Debug ]----------"
	@cd "POSIXThreading" && "$(MAKE)" -f  "POSIXThreading.mk"
clean:
	@echo "----------Cleaning project:[ POSIXThreading - Debug ]----------"
	@cd "POSIXThreading" && "$(MAKE)" -f  "POSIXThreading.mk" clean
