t <html><head><title>GPS-ГЛОНАСС Статус</title>
t <meta http-equiv="refresh" content="10"></head>
i pg_header.inc
t <h2 align=center><br>Статус GPS/ГЛОНАСС приёмника</h2>
t <center>
t <table border=0 width=600><font size="3">
t <tr bgcolor=#aaccff>
# Here begin data setting which is formatted in HTTP_CGI.C module
t <tr><td><img src=pabb.gif>Приём информации от СЕВ</td>
c c j <td><input type=text name=ip value="%s" size=20 maxlength=20></td></tr>
t <tr><td><img src=pabb.gif>Привязка информации к СЕВ</td>
c c i <td><input type=text name=ip value="%s" size=20 maxlength=20></td></tr>
t <tr><td><IMG SRC=pabb.gif>Количество спутников</td>
c c m <td><input type=text name=msk value="%.2d" size=20 maxlength=20></td></tr>
t <tr><td><IMG SRC=pabb.gif>Дата</td>
c c g <td><input type=text name=gw value="%.2d:%.2d:%.4d" size=20 maxlength=20></td></tr>
t <tr><td><IMG SRC=pabb.gif>Время</td>
c c p <td><input type=text name=rp value="%.2d:%.2d:%.2d" size=20 maxlength=20></td></tr>
t <tr><td><IMG SRC=pabb.gif>Широта</td>
c c w <td><input type=text name=ww value="%s" size=20 maxlength=20></td></tr>
t <tr><td><IMG SRC=pabb.gif>Долгота</td>
c c q <td><input type=text name=qp value="%s" size=20 maxlength=20></td></tr>
t </font></table>
t </tr>
c c
t </font></table>
t <form action=tcp.cgi method=post name=form1>
t  <table width=660>
t  <tr><td align="center">
t  <input type=button value="обновить" onclick="location='/gps.cgi'">
t  </td></tr></table>
t  </center>
t </form>
t <p><a href="../picklist.cgi"><b><font size="4">Параметры связи с  GPS/ГЛОНАСС приёмником</font></b></a></p>
. End of script must be closed with period.

