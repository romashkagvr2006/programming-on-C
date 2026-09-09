t <html><head><title>Parametrs SB </title>
t <script language=JavaScript>
t  function formatConfirm(f){
t   if(!confirm('Параметры ЦНРК и АЧХ канала записаны в память')) return;
t   f.submit();
t  }
t </script></head>
i pg_header.inc
t <h2 align=center><br>Относительные коэффициенты передачи<br>
t на нижней и верхней граничных частотах и ЦНРК канала</h2>
t </tr>
t <table border=0 width=715px>
t <tr bgcolor=#aaccff>
t  <th width=5%>Канал</th><th width=20%>К.п НЧ</th><th width=20%>К.п ВЧ</th>
t  <th width=20%>ЦНРК</th>
t </tr>
c n d
t </table>
t <form action=index.htm method=post name=form3>
t <input type=hidden value="yes" name=knprom>
t <p align="center">
t  <input type=button value="Записать параметры в память" onclick="formatConfirm(this.form)">
t </p></form>
i pg_footer.inc
. End of script must be closed with period.

