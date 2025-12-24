cmake CmakeLists.txt
cmake --install .
cmake --build .
copy src\*.txt Debug\*.txt
cd Debug\
analizuojam_straipsnius.exe
pause
