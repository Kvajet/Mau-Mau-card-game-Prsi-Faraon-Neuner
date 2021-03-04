CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic -g
TARGET=maumau

BUILD_DIR=build
MKDIR=mkdir -p

.PHONY: all
all: compile run

.PHONY: compile
compile: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)/ $(TARGET) 2>/dev/null

$(TARGET): $(BUILD_DIR)/CCard.o $(BUILD_DIR)/CDeck.o $(BUILD_DIR)/CGameRegister.o $(BUILD_DIR)/CMauMau.o $(BUILD_DIR)/CRenderer.o $(BUILD_DIR)/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.cpp
	$(MKDIR) $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# .o patterns

$(BUILD_DIR)/CCard.o: src/CCard.cpp src/CCard.h
$(BUILD_DIR)/CDeck.o: src/CDeck.cpp src/CDeck.h src/CCard.h src/CGameRegister.h
$(BUILD_DIR)/CGameRegister.o: src/CGameRegister.cpp src/CGameRegister.h src/CCard.h
$(BUILD_DIR)/CMauMau.o: src/CMauMau.cpp src/CMauMau.h src/CDeck.h src/CCard.h src/CGameRegister.h src/CRenderer.h
$(BUILD_DIR)/CRenderer.o: src/CRenderer.cpp src/CRenderer.h src/CGameRegister.h src/CCard.h
$(BUILD_DIR)/main.o: src/main.cpp src/CMauMau.h src/CDeck.h src/CCard.h src/CGameRegister.h src/CRenderer.h