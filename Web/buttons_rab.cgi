t <html><head><title>Button inputs</title>
t <script language=JavaScript type="text/javascript" src="xml_http.js"></script>
t <script language=JavaScript type="text/javascript">
# Define URL and refresh timeout
t var formUpdate = new periodicObj("buttons.cgx", 1000);
t function periodicUpdate() {
t  if(document.getElementById("refreshChkBox").checked == true) {
t   updateMultiple(formUpdate);
t   periodicFormTime = setTimeout("periodicUpdate()", formUpdate.period); 
t  }
t  else
t   clearTimeout(periodicFormTime);
t }
t </script></head>
i pg_header.inc
t <h3 align="center"><br>Состояние сигналов дистанционного контроля</h3>
t <form action="buttons.cgi" method="post" id="form1" name="form1">
t <table border="0" width=99%><font size="3">
t <tr bgcolor=#aaccff>
t   </tr>
t <tr>
t  <td align="center">
t   <input type="checkbox"  id="button0">Резерв 1
t  </td>
t <tr>
t  <td align="center">
t   <input type="checkbox"  id="button1">Резерв 2
t  </td>
t <tr>
t  <td align="center">
t   <input type="checkbox"  id="button2">Авария сети
t  </td>
t <tr>
t  <td align="center">
t   <input type="checkbox"  id="button3">Авария АКБ
t  </td>
t   <tr>
t  <td align="center">
t   <input type="checkbox"  id="button4">Разряд АКБ
t  </td>
t <tr>
t  <td align="center">
t   <input type="checkbox"  id="button5">Авария УЗИП
t  </td>
t <tr>
t </font></table>
t <p align="center">
t  Сканировать входы:<input type="checkbox" id="refreshChkBox" onclick="periodicUpdate()">
t </p></form>
i pg_footer.inc
. End of script must be closed with period.
