.PHONY: all console_app logger tests test asan tsan clean
all: logger console_app tests

logger:
	$(MAKE) -C logger


console_app: logger
	$(MAKE) -C console_app


tests: logger console_app
	$(MAKE) -C tests

test: tests
	$(MAKE) -C tests test

asan:
	$(MAKE) clean
	$(MAKE) EXTRA_CXXFLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer -g" test

tsan:
	$(MAKE) clean
	$(MAKE) EXTRA_CXXFLAGS="-fsanitize=thread -fno-omit-frame-pointer -g" RUN_PREFIX="setarch $$(uname -m) -R " test

clean:
	$(MAKE) -C logger clean
	$(MAKE) -C console_app clean
	$(MAKE) -C tests clean