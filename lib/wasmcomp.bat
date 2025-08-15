@echo off
call C:/Users/Jaydon/source/repos/emsdk/emsdk_env.bat
scons type=static platform=wasm
pause