t <html><head><title>Button inputs</title>
t <script language=JavaScript type="text/javascript" src="xml_http.js"></script>
t </head>
i pg_header.inc
t <h3 align="center"><br>Управление блоком регистрации</h3>
t <form action="buttons.cgi" method="post" id="form1" name="form1">
t <table border="0" width=99%><font size="3">
#
t  <tr >
t  <td align="right" > Остановить регистрацию </td>
t  <td align="center">
t  <label><input type = "RADIO" NAME = "butt" VALUE="on1" CHECKED><ib></ib></label></td>
t  <td align="center">
t  <label><input type="RADIO"  NAME = "butt" VALUE="on2" ><ib></ib></label></td><td> Запустить регистрацию
t  </td></tr>
#
t <tr>
t  <td align="right"> Фильтрация ФВЧ запрещена  </td>
t <td align="center"> 
t <label><input type="RADIO" NAME = "button" VALUE="on1" CHECKED><ib></ib></label></td>
t  <td align="center">
t <label><input type="RADIO" NAME = "button" VALUE="on2"><ib></ib></label></td><td> Фильтрация ФВЧ разрешена
t  </td></tr>
#
t   <tr>
t  <td align="right">Передача данных на IP адрес = XXX.XXX.XXX.200 запрещена  </td>
t <td align="center">
t <label><input type="RADIO" NAME = "but" VALUE="on1" CHECKED><ib></ib></label></td>
t  <td align="center">
t <label><input type="RADIO" NAME = "but" VALUE="on2" ><ib></ib></label></td><td> передача данных на IP адрес = XXX.XXX.XXX.200 разрешена
t  </td></tr>
t </font></table>
#
#
t <p align="center">
t <script> 
# Define URL and refresh timeout
t var formUpdate = new periodicObj("buttons.cgx", 1000);
#
t function plotTTGraph() {
t  ttVal1 = document.getElementById("tt_value1").value;
t }
#
t function periodicUpdate() {
t   updateMultiple(formUpdate,plotTTGraph);
t   periodicFormTime = setTimeout("periodicUpdate()", formUpdate.period); 
t }
#
t periodicUpdate();
t </script>
t </p></form>
i pg_footer.inc
. End of script must be closed with period.
