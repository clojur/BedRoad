rem  本文件用于从BIM的输出bin目录下复制本子系统运行时需要的各种文件到本系统的bin目录以便打包可运行的程序
rem  project往上三级目录为Main的根目录,由VS调用时当前目录为本工程project文件所在的路径而不是当前批处理文件的位置，手工
rem  启动则当前目录为批处理所在路径，因此本文件如果要手工执行请先切换为与VS中相同的起始路径后再调用
rem	 复制文件时尽量只复制3rd，CommonModules，Frame下的文件，因为这三类文件服务器肯定会有恰当的编译顺序或布
rem  置，确保各子系统复制时文件已经存在，其它地方的文件不建议在此复制，如有必要请注意考虑文件是否先于本文件执行时已经存在

xcopy /s /c /q /r /y .\..\..\..\3rd\release\bin\ToolkitPro1720vc120.dll .\..\..\..\release\bin\RoadBed\


xcopy /s /c /q /r /y .\..\..\..\release\bin\CommonModules\config\*.* .\..\..\..\release\bin\RoadBed\config\
xcopy /s /c /q /r /y .\..\..\..\release\bin\CommonModules\THGridControl.dll .\..\..\..\release\bin\RoadBed\
xcopy /s /c /q /r /y .\..\..\..\release\bin\CommonModules\TH_MathTool.dll .\..\..\..\release\bin\RoadBed\
xcopy /s /c /q /r /y .\..\..\..\release\bin\CommonModules\THControl.dll .\..\..\..\release\bin\RoadBed\
xcopy /s /c /q /r /y .\..\..\..\release\bin\CommonModules\THMathLib.dll .\..\..\..\release\bin\RoadBed\

xcopy /s /c /q /r /y .\..\..\..\release\bin\frame\error_report.exe .\..\..\..\release\bin\RoadBed\
xcopy /s /c /q /r /y .\..\..\..\release\bin\frame\main_application.exe .\..\..\..\release\bin\RoadBed\
del /f /s /q .\..\..\..\release\bin\RoadBed\RoadBed.exe
rename .\..\..\..\release\bin\RoadBed\main_application.exe RoadBed.exe
xcopy /s /c /q /r /y .\..\..\..\release\bin\frame\x_framework.dll .\..\..\..\release\bin\RoadBed\


