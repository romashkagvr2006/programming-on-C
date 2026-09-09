t <html><head><title>Network Settings</title>
t <script language=JavaScript>
t function changeConfirm(f){
t  if(!confirm('Вы действительно хотите поменять\n Сетевые параметры?')) return;
t  f.submit();
t }
t </script></head>
i pg_header.inc
t <h2 align=center><span style='color:red'><br>Сетевые параметры</h2>
t <p><font size="3"><span style='color:red'>На этой странице вы можете поменять настройки <b>Сетевых параметров</b>.
t  После изменения  LAN IP адреса, Вам необходимо поменять  IP адрес в 
t  вашем Интернет  браузере чтобы подключиться к устройству. Будьте <b>особенно внимательны и осторожны</b> при смене
t  <b>LAN IP Address</b> так как ошибка может привести к невозможности подключения устройства.<br><br>
t <form action=network.cgi method=get name=cgi>
t <input type=hidden value="net" name=pg>
t <table border=0 width=99%><font size="4">
t <tr bgcolor=red>
t  <th width=40%>Адреса</th>
t  <th width=60%>Значение</th></tr>
# Here begin data setting which is formatted in HTTP_CGI.C module
t <tr><td><img src=pabb.gif>LAN IP Address</td>
c a i <td><input type=text name=ip value="%d.%d.%d.%d" size=20 maxlength=20></td></tr>
t <tr><td><IMG SRC=pabb.gif>LAN MAC Address</td>
c a m <td><input type=text name=msk value="%.2X.%.2X.%.2X.%.2X.%.2X.%.2X" size=20 maxlength=20></td></tr>
t <tr><td><IMG SRC=pabb.gif>Default Gateway</td>
c a s <td><input type=text name=gw value="%d.%d.%d.%d" size=20 maxlength=20></td></tr>
t <tr><td><IMG SRC=pabb.gif>Remote IP Address</td>
c a g <td><input type=text name=rip value="%d.%d.%d.%d" size=20 maxlength=20></td></tr>
t <tr><td><IMG SRC=pabb.gif>Remote Port</td>
c a p <td><input type=text name=rp value="%.6d" size=20 maxlength=20></td></tr>
t </font></table>
# Here begin button definitions
t <p align=center>
t <input type=button name=set value="запомнить" onclick="changeConfirm(this.form)">
t <input type=reset value="отменить">
t <g4 align=center><br>Для изменения параметров необходимо остановить 
t регистратор подав команду 'O' из командной строки.
t Изменить необходимый параметр и нажать экранную кнопку "запомнить".
t Изменения вступают в силу после перезагрузки командой 'M' из командной строки. 
t </g4>
t </p></form>
. End of script must be closed with period.

