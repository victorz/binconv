CFLAGS = -Wall -pedantic
TARGET = binconv
CC = gcc

all : $(TARGET)

$(TARGET) : binconv.c
