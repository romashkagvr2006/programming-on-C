t <html><head><title> ЦНРК каналов регистратора</title>
i pg_header.inc
t <h2 align=center><br> ЦНРК каналов регистратора</h2>
t <FORM ACTION=picklist.cgi METHOD=POST NAME=CGI>
t <table border=0 width=99%><font size="3">
t <tr bgcolor=#aaccff>
t  <th width=20%>ЦНРК Каналов</th>
t  <th width=20%>CH1</th>
t  <th width=20%>CH2</th>
t  <th width=20%>CH3</th>
t  <th width=20%>CH4</th></tr>
#
t <tr><td><img src="pabb.gif">Группа 1</td>
t   <td align="center">
c B 1  <input type=text name=lcf1 size=8 maxlength=8 value="%s">
t   <td align="center">
c B 2 <input type=text name=lcf2 size=8 maxlength=8 value="%s">
t   <td align="center">
c B 3  <input type=text name=lcf3 size=8 maxlength=8 value="%s">
t   <td align="center">
c B 4  <input type=text name=lcf4 size=8 maxlength=8 value="%s">
#
t <tr><td><img src="pabb.gif">Группа 2</td>
t   <td align="center">
c B 5 <input type=text name=lcd2 size=8 maxlength=8  value="%s">
t   <td align="center">
c B 6  <input type=text name=lcd3 size=8 maxlength=8 value="%s">
t   <td align="center">
c B 7  <input type=text name=lcd4 size=8 maxlength=8 value="%s">
t   <td align="center">
c B 8  <input type=text name=lcd5 size=8 maxlength=8 value="%s">
#
t <tr><td><img src="pabb.gif">Группа 3</td>
t   <td align="center">
c E 3  <input type=text name=lcg1 size=8 maxlength=8 value="%s"></td>
t   <td align="center">
c E 4  <input type=text name=lcg2 size=8 maxlength=8 value="%s"></td>
t   <td align="center">
c E 5  <input type=text name=lcg3 size=8 maxlength=8 value="%s"></td>
t   <td align="center">
c E 6  <input type=text name=lcg4 size=8 maxlength=8 value="%s"></td></tr>
t </table></tr>
#
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