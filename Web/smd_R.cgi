t <html><head><title>Directory</title>
t <script language=JavaScript type="text/javascript" src="xml_http.js"></script>
#  
t </head>
i pg_header.inc
t <h2 align="center">Управление сейсмоприёмниками</h2>
t <FORM ACTION=smd.cgi METHOD=POST NAME=ad>
#
#
t <table class="class_1" border=0 width=815px>
t <tr>
t <th bgcolor=#aaffcc width=99%>Параметры подключенных сейсмоприёмников</th> </tr>
t </table> 
t <table  sborder=0 width=99%>
t <tr>
t  <th bgcolor=#aaccff width=10%>Выбрать сейсмоприемник</th><th bgcolor=#aaccff width=10%>Группа</th>
t <th bgcolor=#aaccff width=10%>Номер</th>
t  <th bgcolor=#aaccff width=10%>Тип</th><th bgcolor=#aaccff width=20%>Коэффициент передачи</th>
t <th bgcolor=#aaccff width=20%>Состояние датчиков</th><th bgcolor=#aaccff width=20%>наклон корпуса, °</th>
t </tr>
c n c
t </table>
#    
#
t <table border="0" width=99%><font size="3">
t <tr>
t <right>
t <td ><img src=pabb.gif>Выберите команду из списка  >></td>
t <td><select name="PICK3" >
#
t <left>
c L1b <option value=b %s>Запросить подключенные сейсмоприемники	</option>
c L1a <option value=a %s>Подключить сейсмоприемник	    	</option>
c L16 <option value=6 %s>Показать параметры сейсмоприёмника     </option> 
c L13 <option value=3 %s>Ориентация по вертикали (ТБСЦ6) 	</option>
c L11 <option value=1 %s>Арретировать датчики 		    	</option> 
c L12 <option value=2 %s>Разарретировать датчики 	   	</option> 
c L14 <option value=4 %s>Вывешивание                         	</option>
c L1c <option value=c %s>Контроль периода маятника (ТБСЦ6)     	</option>
c L1f <option value=f %s>Изменить период маятника (ТБСЦ6)       </option>
c L15 <option value=5 %s>Проверка воды в скважине (кроме ТБСЦ5)	</option>
c L1d <option value=d %s>Изменить коэффициент преобразования	</option>
c L17 <option value=7 %s>Подключить контрольный вход      	</option>
c L18 <option value=8 %s>Отключить контрольный вход       	</option>
c L19 <option value=9 %s>Перевести в ждущий режим  	    	</option   
t    </select></td>
t    </font></table>
t    </tr>
t <tr>
t <td  align="center"><INPUT TYPE=SUBMIT NAME=set VALUE="Выполнить" id="smb" >
t </td>
t </center>
t </tr>
# 
t <table border=0 width=99%>
t <tr> <td>
t До завершения команды, c
c c t <input type=text id="m_time_st" value="%.3d" size=4 maxlength=4></td>
t <td ><label><input type="checkbox"  id="kvit4"><i></i></label> прием данных </td>
t </tr>
t </table>
#
t <hr>
t <br>
#
#
t <table border=0 width=99%><font size="3">
t <tr style="background-color: #aacc99">
t </tr>
#
#
#
t <tr><td><IMG SRC=pabb.gif>Центровка маятника, %</td>
#
t <td align="right">N = </td>
t <td align="left"><input type="text" readonly style="background-color: transparent; border: 0px"
c j 1  size="10" id="sd_value1" value="%4.2f "></td>
#
t <td align="right">E =</td>
t <td align="left"><input type="text" readonly style="background-color: transparent; border: 0px"
c k 1  size="10" id="sd_value2" value="%4.2f "></td>
#
t <td align="right">Z = </td>
t <td align="left"><input type="text" readonly style="background-color: transparent; border: 0px"
c l 1  size="10" id="sd_value3" value="%4.2f "></td>
#
t </tr>
t </font></table>
#
t <br>
t <hr>
#
t <table border=0 width=99%>
t <tr>
t <th bgcolor=#aaffcc width=99%>Квитанции команд</th> </tr>
t </table>
#
t <table border=0 width=99%><font size="3">
t <tr>
t <td ><label><input type="checkbox"  id="kvit0"><i></i></label> Контрольный вход </td>
t <td ><label><input type="checkbox"  id="butt3"><i></i></label> N-разарр </td>
t <td ><label><input type="checkbox"  id="butt0"><i></i></label> N-вывешен</td>
t <td ><label><input type="checkbox"  id="kvit5"><ir></ir></label> Ошибка приема команды</td>
t </tr>
t <tr>
t <td ><label><input type="checkbox"  id="kvit2"><i></i></label> Ориентация по вертикали </td>
t <td ><label><input type="checkbox"  id="butt4"><i></i></label> E-разарр </td>
t <td ><label><input type="checkbox"  id="butt1"><i></i></label> E-вывешен</td>
t <td ><label><input type="checkbox"  id="kvit7"><ir></ir></label> Превышение по току</td>
t </tr>
t <tr>
t <td ><label><input type="checkbox"  id="kvit1"><ir></ir></label> Вода в скважине</td>
t <td ><label><input type="checkbox"  id="butt5"><i></i></label> Z-разарр</td>
t <td ><label><input type="checkbox"  id="butt2"><i></i></label> Z-вывешен</td>
t <td ><label><input type="checkbox"  id="kvit6"><ir></ir></label> Двигатель не включается</td>
t </tr>
t </font></table>
#
t  <script >
# Define URL and refresh timeout
t var formUpdate = new periodicObj("ad.cgx", 500);
#
t function plotADGraph() {
t sdVal1 = document.getElementById("sd1_value").value;
t sdVal2 = document.getElementById("sd2_value").value;
t sdVal3 = document.getElementById("sd3_value").value;
t }
#  
t function periodicUpdateAd() {
t if (document.getElementById("m_time_st").value != 0) {
t updateMultiple(formUpdate,plotADGraph);
t smd_elTime = setTimeout(periodicUpdateAd, formUpdate.period);
t }
t else clearTimeout(smd_elTime);
t }
#    
t periodicUpdateAd();
#
t </script>
#
#
. End of script must be closed with period.
    
    