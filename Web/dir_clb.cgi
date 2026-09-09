t <html><head><title>Directory</title>
t <script language=JavaScript>
t  function formatConfirm(f){
t   if(!confirm('Вы действительно хотите сохранить значения ЦНРК и АЧХ?')) return;
t   f.submit();
t  }
t </script></head>
i pg_header.inc
t <h2 align=center><br>Результаты проверки</h2>
t </tr>
t <table border=0 width=99%>
t <tr bgcolor=#aaccff>
t  <th width=5%>Канал</th><th width=10%>Частота, Гц</th><th width=20%>Амплитуда, квант</th>
t  <th width=10%>Фаза, градус</th>
t  <th width=10%>Относ. Кп</th><th width=10%>Кп, дБ</th><th width=10%>Отклонение Кп, %</th>
t  <th width=15%>ЦНРК</th><th width=10%>Отклонение ЦНРК, %</th>
t </tr>
c n a
t </table>
t <form action=index.htm method=post name=form1>
t <input type=hidden value="yes" name=apdat>
t <p align="center">
t  <input type=button value="Записать результаты проверки на страницу параметров" onclick="formatConfirm(this.form)">
t </p></form>
i pg_footer.inc
. End of script must be closed with period.

