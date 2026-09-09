t <html><head><title>Directory</title>
t <script language=JavaScript>
t  function formatConfirm(f){
t   if(!confirm('Вы действительно хотите отформатировать карту памяти?')) return;
t   f.submit();
t  }
t </script></head>
i pg_header.inc
t <h2 align=center><br>Состояние карты памяти</h2>
t </tr>
t <table border=0 width=600><font size="3">
t <tr><td><IMG SRC=pabb.gif> Свободно N0:</td>
t <left>
c e g <td><input type=text name=gw value="%lld байт" size=20 maxlength=20></td></tr>
t <tr><td><IMG SRC=pabb.gif> Свободно N1:</td>
t <left>
c e f <td><input type=text name=gw value="%lld байт" size=20 maxlength=20></td></tr>
t </font></table>
t <table border=0 width=750>
t <tr bgcolor=#aaccff>
t  <th width=8%>№.</th><th width=20%>Папка</th>
t  <th width=25%>Размер</th><th width=37%>Дата создания</th>
t </tr>
c d
t </table>
t <form action=index.htm method=post name=form1>
t <input type=hidden value="yes" name=format>
t <p align="center">
t  <input type=button value="Форматировать карту памяти" onclick="formatConfirm(this.form)">
t </p></form>
i pg_footer.inc
. End of script must be closed with period.

