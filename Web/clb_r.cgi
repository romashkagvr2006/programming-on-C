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
t <td><img src=pabb.gif>Выбор устройства</td>
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
t <td ><INPUT TYPE=SUBMIT  NAME=set VALUE="Выполнить" id="smb"></td>
t </tr>
t </center>
t </tr>
#
t <table border=0 width=300><font size="3">
t <tr><td>Время проверки, c</td><td>
c c s <input type=text id="cl_time" value="%.4d" size=4 maxlength=4></td>
t </tr>
#
t <table border=0 width=99%><font size="3">
t <tr style="background-color: #ffcc99">
t <p><a href="dir_clb.cgi"><b><font size="5">Показать результат </font></b></a></p>
t </table>
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
