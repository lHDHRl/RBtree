# Название исполнимого файла
TARGET = main.cpp

# Компилятор
CXX = g++

# Флаги компилятора
CXXFLAGS = -std=c++17 -Wall

# Все исходные файлы .cpp в проекте
SRC = $(wildcard *.cpp)

# Все объектные файлы .o
OBJ = $(SRC:.cpp=.o)

# Правило по умолчанию, которое будет выполнено, если не указано ничего конкретного
all: $(TARGET)

# Правило для сборки исполнимого файла
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Правило для компиляции .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка (удаление .o файлов и исполнимого файла)
clean:
	rm -f $(OBJ) $(TARGET)
