rem  ���ļ����ڴ�BIM�����binĿ¼�¸��Ʊ���ϵͳ����ʱ��Ҫ�ĸ����ļ�����ϵͳ��binĿ¼�Ա��������еĳ���
rem  project��������Ŀ¼ΪMain�ĸ�Ŀ¼,��VS����ʱ��ǰĿ¼Ϊ������project�ļ����ڵ�·�������ǵ�ǰ�������ļ���λ�ã��ֹ�
rem  ������ǰĿ¼Ϊ����������·������˱��ļ����Ҫ�ֹ�ִ�������л�Ϊ��VS����ͬ����ʼ·�����ٵ���
rem	 �����ļ�ʱ����ֻ����3rd��CommonModules��Frame�µ��ļ�����Ϊ�������ļ��������϶�����ǡ���ı���˳���
rem  �ã�ȷ������ϵͳ����ʱ�ļ��Ѿ����ڣ������ط����ļ��������ڴ˸��ƣ����б�Ҫ��ע�⿼���ļ��Ƿ����ڱ��ļ�ִ��ʱ�Ѿ�����

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


