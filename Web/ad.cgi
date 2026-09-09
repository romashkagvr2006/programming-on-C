t <html><head><title>Directory</title>
t <script language=JavaScript type="text/javascript" src="xml_http.js"></script>
t <script language=JavaScript type="text/javascript">
# Define URL and refresh timeout
t var formUpdate = new periodicObj("ad.cgx", 1000);
#
t function plotADGraph() {
t  adVal1 = document.getElementById("ad1_value").value;
t  adVal2 = document.getElementById("ad2_value").value;
t  adVal3 = document.getElementById("ad3_value").value;
#
t  sdVal1 = document.getElementById("sd1_value").value;
t  sdVal2 = document.getElementById("sd2_value").value;
t  sdVal3 = document.getElementById("sd3_value").value;
t }
#
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
t </script>
t </head>
i pg_header.inc
t <h2 align="center">Управление сейсмометром</h2>
t <FORM ACTION=ad.cgi METHOD=POST NAME=ad>
#
#
t <table border=0 width=600>
t <tr>
t <th bgcolor=#aaffcc width=80%>Параметры подключенных сейсмоприёмников</th> </tr>
t <table border=0 width=600>
t <tr>
t  <th bgcolor=#aaccff width=15%>Группа</th><th bgcolor=#aaccff width=10%>ИН</th>
t  <th bgcolor=#aaccff width=20%>Тип</th><th bgcolor=#aaccff width=20%>КП</th>
t <th bgcolor=#aaccff width=20%>Состояние датчиков</th><th bgcolor=#aaccff width=15%>наклон корпуса, °</th>
t </tr>
c n c
t </table>
#
#
t <table border="0" width=80%><font size="3">
#
t <tr>
t <right>
t <td ><img src=pabb.gif>Cейсмоприемник подключен к  >> </td>
t <td><select name="PICK7" >
#
#
t <left>
c L31 <option value=1 %s>Каналы группы А    </option> 
c L32 <option value=2 %s>Каналы группы В    </option>
t </select></td></tr>
#
t <br>
#
t <tr>
t <right>
t <td ><img src=pabb.gif>ИН  >> </td>
t <td><select name="PICK8" >
#
#
t <left>
c L41 <option value=1 %s>1 - вертикальный</option> 
c L42 <option value=2 %s>2 - вертикальный</option>
c L43 <option value=3 %s>3 - вертикальный</option> 
c L44 <option value=4 %s>4 - вертикальный</option>
c L45 <option value=5 %s>5 - трёхкомпонентный</option> 
t </select></td></tr>
#
t <br>
# 
t <tr>
t <right>
t <td ><img src=pabb.gif>Выберите команду из списка  >></td>
t <td><select name="PICK3" >
#
t <left>
c L1a <option value=a %s>Подключить сейсмоприемник	    </option>
c L16 <option value=6 %s>Показать параметры сейсмометра     </option> 
c L11 <option value=1 %s>Арретировать датчики 		    </option> 
c L12 <option value=2 %s>Разарретировать датчики 	    </option> 
c L13 <option value=3 %s>Ориентация  			    </option>
c L14 <option value=4 %s>Вывешивание                        </option>
c L15 <option value=5 %s>Проверка воды в скважине           </option>
c L17 <option value=7 %s>Подключить калибровочный вход      </option>
c L18 <option value=8 %s>Отключить калибровочный вход       </option>
c L19 <option value=9 %s>Перевести в ждущий режим 	    </option>
#
t </select></td>
t </font></table>
#
#
t <tr>
t <td align="center"><INPUT TYPE=SUBMIT NAME=set VALUE="Выполнить" id="smb" >
t <input type="checkbox" id="adChkBox" onclick="periodicUpdateAd()">Подтвердить.
t <br>До завершения команды, c
c c t <input type=text id="m_time_st" value="%.3d" size=4 maxlength=4>
t <hr>
t <br>
t </td>
t </center>
t </tr>
#
#
t <table border=0 width=80%><font size="3">
t <tr style="background-color: #aacc99">
t </tr>
#
#
t <tr><td><IMG SRC=pabb.gif>Центровка маятника, %</td>
#
t <td align="right">N = </td>
t <td align="left"><input type="text" readonly style="background-color: transparent; border: 0px"
c j 1  size="10" id="sd_value1" value="%5.3f "></td>
#
t <td align="right">E =</td>
t <td align="left"><input type="text" readonly style="background-color: transparent; border: 0px"
c k 1  size="10" id="sd_value2" value="%5.3f "></td>
#
t <td align="right">Z = </td>
t <td align="left"><input type="text" readonly style="background-color: transparent; border: 0px"
c l 1  size="10" id="sd_value3" value="%5.3f "></td>
#
t </tr>
t </font></table>
#
t <br>
t <hr>
#
t <table border=0 width=600>
t <tr>
t <th bgcolor=#aaffcc width=80%>Квитанции команд</th> </tr>
t </table>
#
t <table border=0 width=70%><font size="3">
t <tr>
t  <td >
t   <input type="checkbox"  id="kvit0">Калибровочный вход </td>
t <td ><input type="checkbox"  id="butt3"> N-разжат </td>
t <td ><input type="checkbox"  id="butt0"> N-вывешен</td>
t <td ><input type="checkbox"  id="kvit5">Ошибка приема команды</td>
t </tr>
t <tr>
t  <td >
t   <input type="checkbox"  id="kvit2">Ориентация МВ </td>
t <td ><input type="checkbox"  id="butt4"> E-разжат </td><td >
t <input type="checkbox"  id="butt1"> E-вывешен</td>
t <td ><input type="checkbox"  id="kvit7">Превышение по току</td>
t </tr>
t <tr>
t <td ></td><td ><input type="checkbox"  id="butt5"> Z-разжат</td>
t <td ><input type="checkbox"  id="butt2"> Z-вывешен</td><td >
t <input type="checkbox"  id="kvit6">Двигатель не включается</td>
t </tr>
t <tr>
t <td ></td><td ></td><td ></td><td ><input type="checkbox"  id="kvit1">Вода в скважине</td>
t </tr>
t </font></table>
#
. End of script must be closed with period.

