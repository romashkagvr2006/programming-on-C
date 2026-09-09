t <html><head><title>Параметры подключенных датчиков</title>
#
t <script language=JavaScript>
t  function formatConfirm(f){
t   if(!confirm('Параметры ЦНРК и АЧХ будут записаны в память')) return;
t   f.submit();
t  }
t </script></head>
#
i pg_header.inc
t <h2 align="center"><br>Параметры сейсмоприемников</h2>
#
t <form action=parametr_sb.cgi method=post name=form3>
t <table border="0" width=715px><font size="3">
t <tr><td><h3 align="center"><br>Группа каналов A</h3></td>
#
t <td>	
c M A <input type=text name=kpa2 size=3 maxlength=3 value="%s"></td>
t <td>  
c M B <input type=text name=kpa2 size=3 maxlength=3 value="%s"></td>
t <td>  
c M C <input type=text name=kpa2 size=3 maxlength=3 value="%s"></td>
t <td>
c M D <input type=text name=kpa2 size=3 maxlength=3 value="%s"></td>
t </tr>
t <tr>
t <td><img src=pabb.gif >Коэффициент преобразования, B*c/м </td><td>
c E c <input type=text name=kpa1 size=8 maxlength=8 value="%s"></td><td>
c E d <input type=text name=kpb1 size=8 maxlength=8 value="%s"></td><td>
c E e <input type=text name=kpc1 size=8 maxlength=8 value="%s"></td><td>
c E f <input type=text name=kpd1 size=8 maxlength=8 value="%s"></td></tr>
#
t <tr>
t <td><img src=pabb.gif >Сопротивление цепи контроля, Ом</td><td>
c E 3 <input type=text name=rca1 size=8 maxlength=8 value="%s"></td><td>
c E 4 <input type=text name=rcb1 size=8 maxlength=8 value="%s"></td><td>
c E 5 <input type=text name=rcc1 size=8 maxlength=8 value="%s"></td><td>
c E 6 <input type=text name=rcd1 size=8 maxlength=8 value="%s"></td></tr>
#
t <tr>
t <td><img src=pabb.gif >Постоянная катушки, A*с*с/м</td><td>
c E 7 <input type=text name=tka1 size=8 maxlength=8 value="%s"></td><td>
c E 8 <input type=text name=tkb1 size=8 maxlength=8 value="%s"></td><td>
c E a <input type=text name=tkc1 size=8 maxlength=8 value="%s"></td><td>
c E b <input type=text name=tkd1 size=8 maxlength=8 value="%s"></td></tr>
#
t <tr><td><h3 align="center"><br>Группа каналов B</h3></td>
#
t <td>	
c M E <input type=text name=kpa2 size=3 maxlength=3 value="%s"></td>
t <td>  
c M F <input type=text name=kpa2 size=3 maxlength=3 value="%s"></td>
t <td>  
c M G <input type=text name=kpa2 size=3 maxlength=3 value="%s"></td>
t <td>
c M H <input type=text name=kpa2 size=3 maxlength=3 value="%s"></td>
t </tr>
t <tr>
t <td><img src=pabb.gif>Коэффициент преобразования, В*c/м </td><td>
c M c <input type=text name=kpa2 size=8 maxlength=8 value="%s"></td><td>
c M d <input type=text name=kpb2 size=8 maxlength=8 value="%s"></td><td>
c M e <input type=text name=kpc2 size=8 maxlength=8 value="%s"></td><td>
c M f <input type=text name=kpd2 size=8 maxlength=8 value="%s"></td></tr>
#
t <tr>
t <td><img src=pabb.gif>Сопротивление цепи контроля, Ом</td><td>
c M 3 <input type=text name=rca2 size=8 maxlength=8 value="%s"></td><td>
c M 4 <input type=text name=rcb2 size=8 maxlength=8 value="%s"></td><td>
c M 5 <input type=text name=rcc2 size=8 maxlength=8 value="%s"></td><td>
c M 6 <input type=text name=rcd2 size=8 maxlength=8 value="%s"></td></tr>
#
t <tr>
t <td><img src=pabb.gif>Постоянная катушки, A*с*с/м</td><td>
c M 7 <input type=text name=tka2 size=8 maxlength=8 value="%s"></td><td>
c M 8 <input type=text name=tkb2 size=8 maxlength=8 value="%s"></td><td>
c M a <input type=text name=tkc2 size=8 maxlength=8 value="%s"></td><td>
c M b <input type=text name=tkd2 size=8 maxlength=8 value="%s"></td></tr>
#
t </table>
#
t <input type=hidden value="yes" name=sbprom>
t <p align="center">
t  <input type=button value="Записать параметры в память" onclick="formatConfirm(this.form)">
#
t </p></form>
. End of script must be closed with period
