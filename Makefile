
Batch : build\ProjectConfig.exe 

Build\ProjectConfig.exe : Src\main.c Src\ProjectConfig.c Inc\ProjectConfig.h
	gcc -IInc -D BATCH_REQUIRE Src\main.c Src\ProjectConfig.c -o build\ProjectConfig.exe

clean :
	del build\*.exe