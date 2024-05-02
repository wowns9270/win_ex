@echo off

rem CMake 실행
cmake -S . -B build

rem 빌드 디렉토리로 이동
cd build

rem 빌드 수행
cmake --build .

rem 빌드 완료 후 디렉토리 이동
cd ..