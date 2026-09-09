t <html><head><title>Контроль функционирования</title>
t <script language=JavaScript type="text/javascript" src="xml_http.js"></script>
t </head>
i pg_header.inc
t <h2 align="center"><br>Контроль функционирования</h2>
#
t <FORM ACTION=clb.cgi METHOD=POST NAME=CGI>
t <table border="0" width=99%><font size="3">
t </tr>
t <tr>
#
t <left>
t <td><img src=pabb.gif>Выбор команды</td>
t <td><select name="PICK4" >
#
t <left>
c L21 <option value=1 %s>Контроль регистратора от внутреннего генератора</option> 
c L22 <option value=2 %s>Контроль канала от внутреннего генератора</option>
c L23 <option value=3 %s>Контроль канала от внешнего генератора</option>
c L24 <option value=4 %s>Контроль регистратора от внешнего генератора</option>
c L25 <option value=5 %s>Дискретный сигнал 5В, 10с</option>
#
t <tr><td><img src=pabb.gif>Частота сигнала, Гц</td>
c E 2 <td><input type=text name=fclb size=8 maxlength=8 value="%s"></td></tr>
#
t <tr><td><img src=pabb.gif>Амплитуда сигнала, В</td>
c E 9 <td><input type=text name=aclb size=8 maxlength=8 value="%s"></td></tr>
#
t </select></td>
t </table>
t </tr>
t <tr>
t <p align=center>
t <td  align="center"><INPUT TYPE=SUBMIT  NAME=set VALUE="Выполнить" id="smb"></td>
t </tr>
t </center>
#
t <tr> <td>
t До завершения команды, c
c c s <input type=text id="cl_time" value="%.3d" size=4 maxlength=4>
t <br></td></tr>
t </table>
#
t <table border=0 width=99%><font size="3">
t <tr style="background-color: #ffcc99">
t <p><a href="dir_clb.cgi"><b><font size="5">Показать результат </font></b></a></p>
t </tr>
t </table>
t <table>
t <g3 align=center><br> 
t ЦНРК каналов проверяется на опорной частоте равной 1 Гц<br>
t при установленной частоте дискретизации 10 и 25 Гц<br>
t и опорной частоте 5 Гц при установленной частоте дискретизации<br>
t от 40 до 250 Гц.<br> 
t </g3> </table>
t </p></form>
#
t <script >
# Define URL and refresh timeout
t var formUpdate = new periodicObj("clb.cgx", 1000);
#
t function plotCLGraph() {
t  cltime = document.getElementById("cl_time").value;
t }
#
t function periodicUpdateCl() {
t  if(document.getElementById("cl_time").value != 0) {
t   updateMultiple(formUpdate,plotCLGraph);
t   ad_elTime = setTimeout(periodicUpdateCl, formUpdate.period);
t  }
t  else
t   clearTimeout(ad_elTime);
t }
#
t periodicUpdateCl();
#
t </script>
. End of script must be closed with period
