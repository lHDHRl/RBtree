# Имя исполняемого файла
TARGET = main

# Компилятор
CXX = g++

# Флаги компилятора
CXXFLAGS = -std=c++17 -Wall

# Все исходные файлы (.cpp) в проекте
SRC = main.cpp RedBlackTree.cpp src/LinkedList.cpp

# Все объектные файлы (.o)
OBJ = $(SRC:.cpp=.o)

# Правило по умолчанию для сборки проекта
all: $(TARGET)

# Правило для сборки исполняемого файла из объектных файлов
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Правило для компиляции .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка (удаление объектных файлов и исполняемого файла)
clean:
ifeq ($(OS),Windows_NT)
	del /Q $(OBJ) $(TARGET).exe 2> nul
else
	rm -f $(OBJ) $(TARGET)
endif
