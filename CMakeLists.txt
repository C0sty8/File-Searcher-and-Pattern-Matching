cmake_minimum_required(VERSION 4.1)
project(PaternSearcherInFiles C)

set(CMAKE_C_STANDARD 11)

add_executable(PaternSearcherInFiles main.c
        Structures/RBT.c
        Structures/RBT.h
        Structures/Trie.h
        Structures/Trie.c
        Utils/FileReadingUtils.c
        Utils/FileReadingUtils.h)
