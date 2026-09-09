t <html><head><title>МЕТЕОСТАНЦИЯ Статус</title>
t <meta http-equiv="refresh" content="5"></head>
i pg_header.inc
t <h2 align=center><br>Метеоданные</h2>
t <center>
t <table border=0 width=600><font size="3">
t <tr bgcolor=#aaccff>
# Here begin data setting which is formatted in HTTP_CGI.C module
t <tr><td><img src=pabb.gif>Атмосферное давление</td>
c f j <td><input type=text name=ip value="%5.2f гПа" size=15 maxlength=15></td></tr>
t <tr><td><img src=pabb.gif>Температура воздуха</td>
c f i <td><input type=text name=ip value="%5.2f °С" size=15 maxlength=15></td></tr>
t <tr><td><IMG SRC=pabb.gif>относительная влажность воздуха </td>
c f m <td><input type=text name=msk value="%5.2f %%" size=15 maxlength=15></td></tr>
t <tr><td><IMG SRC=pabb.gif>направление ветра</td>
c f g <td><input type=text name=gw value="%5.2f °" size=15 maxlength=15></td></tr>
t <tr><td><IMG SRC=pabb.gif>скорость ветра</td>
c f p <td><input type=text name=rp value="%5.2f м/с" size=15 maxlength=15></td></tr>
t <tr><td><h2 align=center><br>Температура в регистраторе</h2>
c f r <td><input type=text name=ip value="%5.2f °С" size=15 maxlength=15></td></tr>
t </font></table>
t </tr>
c f
t </font></table>
t <form action=tcp.cgi method=post name=form1>
t  <table width=660>
t  <tr><td align="center">
t  <input type=button value="обновить" onclick="location='/meteo.cgi'">
t  </td></tr></table>
t  </center>
t </form>
. End of script must be closed with period.

