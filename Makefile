.PHONY: build build-release run run-release clean

# Build directories
BUILD_DIR = build
BUILD_DIR_RELEASE = build-release

# Default build (debug)
build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug .. && make

# Release build
build-release:
	mkdir -p $(BUILD_DIR_RELEASE)
	cd $(BUILD_DIR_RELEASE) && cmake -DCMAKE_BUILD_TYPE=Release .. && make

# Run debug version
run: build
	./$(BUILD_DIR)/stratego

# Run release version
run-release: build-release
	./$(BUILD_DIR_RELEASE)/stratego

clean:
	rm -rf $(BUILD_DIR) $(BUILD_DIR_RELEASE)
