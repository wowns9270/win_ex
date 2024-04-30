cmake_minimum_required(VERSION 3.10)
project(main)

include_directories( ../include) 


# 소스 파일 추가
set(SOURCES 
    main.cpp
)

# 실행 파일 생성
add_executable(main ${SOURCES})

