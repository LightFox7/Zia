##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

################################################################################
# Config Vars
NAME					=	zia

BUILD_DIR				=	build

CP						=	cp

#################################################
# Server
SERVER_BIN				=	zia

SERVER_DIR				=	server

#################################################
# Tests
CRITERION_BIN			=	unit_tests


################################################################################
.DEFAULT: all

all: $(NAME)

$(NAME): server

log: OPTIONS +=-DUSE_LOG=ON
log: $(NAME)

debug: OPTIONS +=-DUSE_DEBUG=ON
debug: $(NAME)


################################################################################
# SERVER RULES
server:
	@mkdir -p build && cd build && conan install .. --build=missing && cmake .. -G "Unix Makefiles" && cmake -build . && make
	@$(CP) $(BUILD_DIR)/bin/$(SERVER_BIN) $(BUILD_DIR)
	@$(CP) $(BUILD_DIR)/bin/$(SERVER_BIN) .

server_fclean:
	@$(RM) -r $(SERVER_BIN)


################################################################################
# TESTS RULES
tests_run: fclean
	@$(MAKE) -j `nproc` --no-print-directory -C $(BUILD_DIR) $(CRITERION_BIN)
	-@cp $(BUILD_DIR)/bin/$(CRITERION_BIN) .
	@./$(CRITERION_BIN)
	@gcovr -r . -s --exclude='tests|lib' --exclude='BabelCommon/Utils/Runnable|BabelCommon/Utils/Logger|BabelCommon/Network/Sockets'
	@gcovr -b . -s --exclude='tests|lib' --exclude='BabelCommon/Utils/Runnable|BabelCommon/Utils/Logger|BabelCommon/Network/Sockets'

gh_tests_run: OPTIONS +=-DGH_TESTS=ON
gh_tests_run: fclean
	@cmake $(OPTIONS) -B $(BUILD_DIR)
	@$(MAKE) -j `nproc` --no-print-directory -C $(BUILD_DIR) $(CRITERION_BIN)
	-@cp $(BUILD_DIR)/bin/$(CRITERION_BIN) .
	@./$(CRITERION_BIN)


################################################################################
# OTHERS RULES

mouli-install: fclean
	#-conan remote add conan-center https://bintray.com/conan/conan-center
	-conan remote add tech-repo https://api.bintray.com/conan/epitech/public-conan
	-conan remote add public-repo https://api.bintray.com/conan/bincrafters/public-conan

	@mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && conan install .. --build=missing

modules:
	-make -C modules

clean-modules:
	-make clean-modules -C modules

clean:
	@$(RM) -r $(BUILD_DIR)

fclean: clean server_fclean clean-modules
	@$(RM) -r $(BUILD_DIR) $(CRITERION_BIN)

re: fclean all modules

.PHONY: all $(NAME) server tests_run mouli modules
.PHONY: server_fclean clean clean-modules fclean re