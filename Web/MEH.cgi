t <html><head><title>AD Input</title>
t <script language=JavaScript type="text/javascript" src="xml_http.js"></script>
t <script language=JavaScript type="text/javascript">
# Define URL and refresh timeout
t var formUpdate = new periodicObj("ad.cgx", 1000);
#
t function plotADGraph() {
t  adVal1 = document.getElementById("ad_valu1").value;
t  adVal2 = document.getElementById("ad_valu2").value;
t  adVal3 = document.getElementById("ad_valu3").value;
t  numVal1 = parseInt(adVal1, 16);
t  numVal2 = parseInt(adVal2, 16);
t  numVal3 = parseInt(adVal3, 16);
t  voltsVal1 = (3.3*numVal1)/1024;
t  voltsVal2 = (3.3*numVal2)/1024;
t  voltsVal3 = (3.3*numVal3)/1024;
t  tableSize1 = (numVal1*100/1024);
t  tableSize2 = (numVal2*100/1024);
t  tableSize3 = (numVal3*100/1024);
t  document.getElementById("ad_table1").style.width = (tableSize1 + '%');
t  document.getElementById("ad_table2").style.width = (tableSize2 + '%');
t  document.getElementById("ad_table3").style.width = (tableSize3 + '%');
t  document.getElementById("ad_volts1").value = (voltsVal1.toFixed(3) + ' V');
t  document.getElementById("ad_volts2").value = (voltsVal2.toFixed(3) + ' V');
t  document.getElementById("ad_volts3").value = (voltsVal3.toFixed(3) + ' V');
t }
#
t function plotCLGraph() {
t  cltime = document.getElementById("m_time_st").value;
t }
#
t function periodicUpdateAd() {
t  if(document.getElementById("adChkBox").checked == true) {
t   updateMultiple(formUpdate,plotADGraph);
t   ad_elTime = setTimeout(periodicUpdateAd, formUpdate.period);
t  }
t  else
t   clearTimeout(ad_elTime);
t }
#
#
t </script></head>
i pg_header.inc
t <h2 align="center"><br>Управление механическими командами</h2>
#
t <FORM ACTION=ad.cgi METHOD=POST NAME=CGI>
t <table border="0" width=99%><font size="3">
t <tr bgcolor=#aaccff>
t </tr>
t <tr>
#
t <right>
t <td><img src=pabb.gif>Выберите команду из списка  >></td>
t <td><select name="PICK3" >
#
t <left>
c L1a <option value=a %s>Подключить сейсмоприемник	    </option> 
c L11 <option value=1 %s>Арретировать датчики 		    </option> 
c L12 <option value=2 %s>Разарретировать датчики 	    </option> 
c L13 <option value=3 %s>Ориентация  			    </option>
c L14 <option value=4 %s>Вывешивание                        </option>
c L15 <option value=5 %s>Проверка воды в скважине           </option>
c L16 <option value=6 %s>Показать углы наклона сейсмометра  </option>
c L17 <option value=7 %s>Подключить калибровочный вход      </option>
c L18 <option value=8 %s>Отключить калибровочный вход       </option>
c L19 <option value=9 %s>Перейти в ждущий режим 	    </option>
#
t </select></td>
t </font></table>
t </tr>
t <tr>
t <p align=center>
t <td ><INPUT TYPE=SUBMIT NAME=set VALUE="Выполнить" id="smb" ></td>
t </tr>
t </center>
t </form>
t </tr>
#
t <form action="ad.cgi" method="post" id="form1" name="form1">
t <table border="0" width=99%><font size="3">
t <tr bgcolor=#ffff99>
t  <th width=90%>Квитанции команд</th>
t </tr>
t <tr>
t  </td>
t <tr>
t  <td align="center">
t   <input type="checkbox"  id="button3">Ориентация МГ
t   <input type="checkbox"  id="button2">Ориентация МВ
t  </td>
t <tr>
t  <td align="center">
t   <input type="checkbox"  id="button5">Разарретирование
t   <input type="checkbox"  id="button4">Арретирование
t  </td>
t <tr>
t  <td align="center">
t   <input type="checkbox"  id="button6">Вывешивание
t  </td>
t <tr bgcolor=#15ff99>
t  <th width=90%>Канал</th>
t </tr>
t <tr>
t  <td align="center">
t   <input type="checkbox"  id="butt0"> X
t   <input type="checkbox"  id="butt1"> Y
t   <input type="checkbox"  id="butt2"> Z
t  </td>
t <tr bgcolor=#ffff99>
t  <th width=90%>Отклонение команды</th>
t </tr>
t <tr>
t <tr bgcolor=#ff5555>
t  <td align="center">
t   <input type="checkbox"  id="button1">Превышение по току
t  </td>
t <tr bgcolor=#ff5555>
t  <td align="center">
t   <input type="checkbox"  id="button0">Превышение по времени
t  </td>
t <tr bgcolor=#ff5555>
t  <td align="center">
t   <input type="checkbox"  id="button7">Превышение допустимого наклона
t  </td>
t <tr>
#
t </font></table>
#
t <form action="ad.cgi" method="post" name="ad">
t <input type="hidden" value="ad" name="pg">
t <table border=0 width=99%><font size="3">
t <tr style="background-color: #aacc99">
t </tr>
t <tr>
#
t <tr><td><IMG SRC=pabb.gif>Наклон сейсмодатчика</td>
c f x <td><input type=text id="ad_table1" value="%6.3f °" size=6 maxlength=6></td>
t <td>NS</td>
c f y <td><input type=text id="ad_table2" value="%6.3f °" size=6 maxlength=6></td>
t <td>EW</td>
c f z <td><input type=text id="ad_table3" value="%6.3f °" size=6 maxlength=6></td>
t <td>SUM</td></tr>
#
t <tr><td><IMG SRC=pabb.gif>Наклон маятника</td>
c f a <td><input type=text id="ad_volts1" value="%6.3f %%" size=6 maxlength=6></td>
t <td>N</td>
c f b <td><input type=text id="ad_volts2" value="%6.3f %%" size=6 maxlength=6></td>
t <td>E</td>
c f c <td><input type=text id="ad_volts3" value="%6.3f %%" size=6 maxlength=6></td>
t <td>V</td></tr>
#
t </tr>
t </font></table>
t  </center>
t </form>
#
t <table border=0 width=300><font size="3">
t <tr><td>До завершения команды, c</td>
c c t <td><input type=text id="m_time_st" value="%.4d" size=4 maxlength=4></td></tr>
t </tr>
#
t </font></table>
t <p align=center>
t Показывать время<input type="checkbox" id="adChkBox"  onclick="periodicUpdateAd()">
t </p></form>
. End of script must be closed with period
