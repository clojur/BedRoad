rem  ���ļ����ڴ�BIM�����binĿ¼�¸��Ʊ���ϵͳ����ʱ��Ҫ�ĸ����ļ�����ϵͳ��binĿ¼�Ա��������еĳ���
rem  project��������Ŀ¼ΪMain�ĸ�Ŀ¼,��VS����ʱ��ǰĿ¼Ϊ������project�ļ����ڵ�·�������ǵ�ǰ�������ļ���λ�ã��ֹ�
rem  ������ǰĿ¼Ϊ����������·������˱��ļ����Ҫ�ֹ�ִ�������л�Ϊ��VS����ͬ����ʼ·�����ٵ���
rem	 �����ļ�ʱ����ֻ����3rd��CommonModules��Frame�µ��ļ�����Ϊ�������ļ��������϶�����ǡ���ı���˳���
rem  �ã�ȷ������ϵͳ����ʱ�ļ��Ѿ����ڣ������ط����ļ��������ڴ˸��ƣ����б�Ҫ��ע�⿼���ļ��Ƿ����ڱ��ļ�ִ��ʱ�Ѿ�����

xcopy /s /c /q /r /y .\..\..\..\3rd\bin\ToolkitPro1720vc120D.dll .\..\..\..\debug\bin\RoadBed\


xcopy /s /c /q /r /y .\..\..\..\debug\bin\CommonModules\config\*.* .\..\..\..\debug\bin\RoadBed\config\
xcopy /s /c /q /r /y .\..\..\..\debug\bin\CommonModules\THGridControlD.dll .\..\..\..\debug\bin\RoadBed\
xcopy /s /c /q /r /y .\..\..\..\debug\bin\CommonModules\TH_MathToolD.dll .\..\..\..\debug\bin\RoadBed\
xcopy /s /c /q /r /y .\..\..\..\debug\bin\CommonModules\THControlD.dll .\..\..\..\debug\bin\RoadBed\
xcopy /s /c /q /r /y .\..\..\..\debug\bin\CommonModules\THMathLibD.dll .\..\..\..\debug\bin\RoadBed\

xcopy /s /c /q /r /y .\..\..\..\debug\bin\frame\error_report.exe .\..\..\..\debug\bin\RoadBed\
xcopy /s /c /q /r /y .\..\..\..\debug\bin\frame\main_application_d.exe .\..\..\..\debug\bin\RoadBed\
del /f /s /q .\..\..\..\debug\bin\RoadBed\RoadBed_d.exe
rename .\..\..\..\debug\bin\RoadBed\main_application_d.exe RoadBed_d.exe
xcopy /s /c /q /r /y .\..\..\..\debug\bin\frame\x_framework_d.dll .\..\..\..\debug\bin\RoadBed\


