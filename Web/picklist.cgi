t <html><head><title>Установки параметров связи с GPS/ГЛОНАСС приёмником</title>
i pg_header.inc
t <h2 align=center><br>Установки параметров связи с GPS/ГЛОНАСС приёмником</h2>
t <FORM ACTION=picklist.cgi METHOD=POST NAME=CGI>
t <table border=0 width=99%><font size="3">
t <tr bgcolor=#aaccff>
t  <th width=40%>Параметр</th>
t  <th width=60%>Значение</th></tr>
#
t <td><img src=pabb.gif>Протокол передачи</td>
t <td><select name="PICK2" >
# 
c R11 <option value=1 %s>NMEA </option> 
c R12 <option value=2 %s>BINARY </option> 
#
t </select></td>
t </tr>
t <tr>
#
t <td><img src=pabb.gif>Скорость передачи</td>
t <td><select name="PICK1" >
#
c P11 <option value=1 %s>4800 </option> 
c P12 <option value=2 %s>9600 </option> 
c P13 <option value=3 %s>19200 </option>
c P14 <option value=4 %s>38400 </option>
#
t </select></td>
t </tr>
t <tr>
#
t <td><img src=pabb.gif>Чётность</td>
t <td><select name="PICK5" >
# 
c Q11 <option value=1 %s>Нечет </option> 
c Q12 <option value=2 %s>Чёт </option> 
c Q13 <option value=3 %s>Нет </option> 
c Q14 <option value=4 %s>Маркер (1) </option> 
c Q15 <option value=5 %s>Пробел (0) </option> 
#
t </select></td>
t </tr>
t <tr>
#
t <td><img src=pabb.gif>Стоповые биты</td>
t <td><select name="PICK6" >
#
c S11 <option value=1 %s>1 </option> 
c S12 <option value=2 %s>2 </option> 
#
t </select></td>
t </tr>
t <tr>
t <td ><INPUT TYPE=SUBMIT NAME=set VALUE="запомнить" id="smb"></td>
t </tr>
t </center>
t </form>
t </body>
t </html>
.