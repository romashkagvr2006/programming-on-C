t <html><head><title>Форматирование карты памяти</title>
t <script language=JavaScript>
t  function formatConfirm(f){
t   if(!confirm('Вы действительно хотите отформатировать карту памяти?')) return;
t   f.submit();
t  }
t </script></head>
i pg_header.inc
t <h2 align=center><br>Форматирование карты памяти</h2>
t <p><font size="3"><br>Перед первым использованием или в случае повреждения FAT системы
t  Вам необходимо произвести форматирование карты памяти.<br><br></font></p>
t <form action=index.htm method=post name=form1>
t <p><font size="3"><br>Метка карты памяти:
c b 1 <input type=text name=label size=11 maxlength=11 value="%s">
t </font></p>
t <input type=hidden value="yes" name=format>
t <p align="center">
t  <input type=button value="Форматировать карту памяти" onclick="formatConfirm(this.form)">
t </p></form>
i pg_footer.inc
. End of script must be closed with period.
