<HTML>
<HEAD>
<TITLE> Testing C++Builder ASP </TITLE>
</HEAD>
<BODY>
<CENTER>
<H3> You should see the results of your C++Builder Active Server method below </H3>
</CENTER>
<HR>
<%
   Set CBuilderASPObj = Server.CreateObject("RocPcServidor.cRocPcServidor")
   CBuilderASPObj.Foto(0,0,768,512,2,1,0,784,520,0,0);
%>
<HR>
</BODY>
</HTML>