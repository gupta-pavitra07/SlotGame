cp main.cpp main.cpp.bak
cp test_crash.cpp main.cpp
cd build && make -j4
lldb ./SlotGameQt -o "run" -o "bt" -o "quit"
cp ../main.cpp.bak ../main.cpp
