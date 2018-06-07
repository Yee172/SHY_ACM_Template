@echo off
:loop  
    data.exe > data.txt
    main.exe < data.txt > myout.txt
    stdd.exe < data.txt > stdout.txt
    fc myout.txt stdout.txt
if not errorlevel 1 goto loop  
pause
goto loop