t <html><head><title>Button inputs</title>
t <script language=JavaScript type="text/javascript" src="xml_http.js"></script>
t </head>
i pg_header.inc
t <h3 align="center"><br>Состояние сигналов дистанционного контроля</h3>
t <form action="buttons.cgi" method="post" id="form1" name="form1">
t <table border="0" width=99%><font size="3">
t <tr >
t  <td align="center">
t <label><input type="checkbox" id="button0"><ib></ib></label></td><td> Резерв 1
t  </td></tr>
t <tr>
t  <td align="center">
t <label><input type="checkbox" id="button1"><ib></ib></label></td><td> Резерв 2
t  </td></tr>
t <tr>
t  <td align="center">
t <label><input type="checkbox" id="button2"><ib></ib></label></td><td> Авария сети
t  </td></tr>
t <tr>
t  <td align="center">
t <label><input type="checkbox" id="button3"><ib></ib></label></td><td> Авария АКБ
t  </td></tr>
t   <tr>
t  <td align="center">
t <label><input type="checkbox" id="button4"><ib></ib></label></td><td> Разряд АКБ
t  </td></tr>
t <tr>
t  <td align="center">
t <label><input type="checkbox" id="button5"><ib></ib></label></td><td> Авария УЗИП
t  </td></tr>
t </font></table>
#
t <table border="0" width=99%><font size="3">
t <tr>
t <td align="center">Температура в регистраторе,° = 
t <align="left"><input type="text" readonly style="background-color: transparent; border: 0px"
c u 1  size="10" id="tt_value1" value="%5.3f "></td>
t </tr>
#
t </font></table>
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
