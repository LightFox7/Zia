##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##


modules:
	@mkdir -p LibSo
	@mkdir -p build && cd build && cmake .. && make && mv *.so ../LibSo


clean-modules:
	@rm -rf build
	@rm -rf LibSo


re: clean-modules modules

.PHONY: modules clean-modules
