## ChibiOS/Gwen, a Gwen integration into ChibiOS/GFX

### Using as a static library: 
##### Only compile once, best for development
*   Run **_make_** in the ChibiOS-Gwen main folder
*   Include **_gfx.mk_** and _**gwen-lib.mk**_ to your ChibiOS project Makefile
*   Add _**$(GWENLIB)**_ to your _**ULIBDIR**_ property to your ChibiOS project Makefile
*   Add _**-lgwen-cm4(d)**_ or _**-lgwen-cm3(d)**_ to your _**ULIBS**_ property in the ChibiOS project Makefile

### Compiling in the user program:
##### Will recompile gwen for each Makefile change and each project
*   Include _**gfx.mk**_ and _**gwen.mk**_ to your ChibiOS project Makefile
*   Will be compiled with your program, best if you use special GCC flags
