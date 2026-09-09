t <html><head><title>Установки параметров регистратора</title>
i pg_header.inc
t <h1 align=center><br>Установки параметров регистратора</h1>
t <FORM ACTION=parametr.cgi METHOD=POST NAME=CGI>
#
#
t <table border=0 width=830px><font size="4">
t <tr style="background-color: #aacc99">
#
t  <th width=50%>Параметр</th>
t  <th width=50%>Значение</th></tr>
#
t <tr><td><img src=pabb.gif>Имя регистратора (не более 5 символов)</td>
c E 1 <td><input type=text name=lcd1 size=8 maxlength=8 value="%s"></td></tr>
#
#
t <td><img src=pabb.gif>Группа каналов A</td>
c b 0 <td>	<label><input type=checkbox name=led0  %s><i></i></label> 
c E A <input type=text name=lcdA size=3 maxlength=3 value="%s">
c b 1     	<label><input type=checkbox name=led1  %s><i></i></label> 
c E B <input type=text name=lcdB size=3 maxlength=3 value="%s">
c b 2     	<label><input type=checkbox name=led2  %s><i></i></label>
c E C <input type=text name=lcdC size=3 maxlength=3 value="%s">
c b 3     	<label><input type=checkbox name=led3  %s><i></i></label>
c E D <input type=text name=lcdD size=3 maxlength=3 value="%s"> </td></tr>
t </td>
t </tr>
#
t <td align="center">Частота выдачи данных, Гц</td>
t <td><select name="PARA2" >
# 
c D19 <option value=9 %s>10 </option> 
c D1a <option value=a %s>25 </option>
c D17 <option value=7 %s>40 </option> 
c D1c <option value=c %s>50 </option> 
c D1d <option value=d %s>100 </option> 
c D1e <option value=e %s>125 </option> 
c D1g <option value=g %s>250 </option> 
#
t </select></td>
t </tr>
#
t <td align="center">Коэффициент усиления АЦП</td>
t <td><select name="PARA4" >
# 
c K11 <option value=1 %s>1 </option> 
c K12 <option value=2 %s>2 </option> 
c K13 <option value=3 %s>4 </option> 
c K14 <option value=4 %s>8 </option> 
#
#
t <tr>
t <td align="center">Фильтрация выходных данных (ФВЧ)</td>
t <td><select name="PARA3" >
#
c F11 <option value=1 %s>нет </option> 
c F12 <option value=2 %s>0,02 </option>  
c F13 <option value=3 %s>0,5 </option>  
#
t </select></td>
t <tr>
#
t <tr>
t <td><img src=pabb.gif>Группа каналов B</td>
c v 0     <td>  <label><input type=checkbox name=lad0  %s><i></i></label>
c E E <input type=text name=lcdE size=3 maxlength=3 value="%s"> 
c v 1     	<label><input type=checkbox name=lad1  %s><i></i></label>
c E F <input type=text name=lcdF size=3 maxlength=3 value="%s"> 
c v 2     	<label><input type=checkbox name=lad2  %s><i></i></label>
c E G <input type=text name=lcdG size=3 maxlength=3 value="%s"> 
c v 3           <label><input type=checkbox name=lad3  %s><i></i></label>
c E H <input type=text name=lcdH size=3 maxlength=3 value="%s"> </tr>
t </td>
t </tr>
#
t <td align="center">Частота выдачи данных, Гц</td>
t <td><select name="PIRA2" >
# 
c D29 <option value=9 %s>10 </option> 
c D2a <option value=a %s>25 </option>
c D27 <option value=7 %s>40 </option> 
c D2c <option value=c %s>50 </option> 
c D2d <option value=d %s>100 </option> 
c D2e <option value=e %s>125 </option> 
c D2g <option value=g %s>250 </option> 
#
t </select></td>
t </tr>
#
t <td align="center">Коэффициент усиления АЦП</td>
t <td><select name="PIRA4" >
# 
c K21 <option value=1 %s>1 </option> 
c K22 <option value=2 %s>2 </option> 
c K23 <option value=3 %s>4 </option> 
c K24 <option value=4 %s>8 </option> 
c K25 <option value=5 %s>16 </option> 
c K26 <option value=6 %s>32 </option> 
c K27 <option value=7 %s>64 </option> 
#
#
t <tr>
t <td align="center">Фильтрация выходных данных (ФВЧ)</td>
t <td><select name="PIRA3" >
#
c F21 <option value=1 %s>нет </option> 
c F22 <option value=2 %s>0,02 </option>  
c F23 <option value=3 %s>0,5 </option>  
#
t </select></td>
t <tr>
#
#
t <td><img src=pabb.gif>Время накопления данных, с</td>
t <td><select name="PARA1" >
#
c N11 <option value=1 %s>1 </option> 
c N12 <option value=2 %s>10 </option> 
#
t </select></td>
t </tr>
#
t <tr><td><img src=pabb.gif>Размер кольцевого буфера в часах (от 1 до 240).</td>
c E h <td><input type=text name=lcd2 size=3 maxlength=3 value="%s"></td></tr>
#
t  </font></table></td></tr>
#
#
t <td ><INPUT TYPE=SUBMIT NAME=set VALUE="запомнить" id="smb"></td>
t <br>Для изменения параметров необходимо остановить 
t регистратор подав команду 'O' на странице команды. Изменить <br>
t необходимый параметр и нажать экранную кнопку "запомнить".<br>
t Изменения вступают в силу после перезагрузки командой 'M'.
t </tr>
t </center>
t </form>
t </body>
t </html>
.