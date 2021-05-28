﻿<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ShareConfigList.aspx.cs" Inherits="Game.Web.Module.AppManager.ShareConfigList" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <link href="../../styles/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="../../scripts/common.js"></script>

    <script type="text/javascript" src="../../scripts/comm.js"></script>

    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="title">
        <tr>
            <td width="19" height="25" valign="top" class="Lpd10">
                <div class="arr">
                </div>
            </td>
            <td width="1232" height="25" valign="top" align="left">
                你当前位置：系统维护 - 每日分享管理
            </td>
        </tr>
    </table>
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" class="Tmg7">
        <tr>
            <td height="28">
                <ul>
                    <li class="tab1">每日分享配置</li>
                    <li class="tab2" onclick="Redirect('ShareLogList.aspx')">分享记录</li>
                    
                </ul>
            </td>
        </tr>
    </table>
    <div id="content">
      <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
          <td height="39" class="titleOpBg">
          </td>
        </tr>
      </table>
        <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" class="box" id="list">
            <tr align="center" class="bold">
              <td class="listTitle2">
                管理
              </td>
              <td class="listTitle2">
                每日分享次数
              </td>
              <td class="listTitle2">
                每日分享获得金币
              </td>
              <td class="listTitle2">
                每日分享获得钻石
              </td>
              <td class="listTitle2">
                状态
              </td>
            </tr>
            <asp:Repeater ID="rptDataList" runat="server">
                <ItemTemplate>
                    <tr align="center" class="list" onmouseover="currentcolor=this.style.backgroundColor;this.style.backgroundColor='#caebfc';this.style.cursor='default';"
                        onmouseout="this.style.backgroundColor=currentcolor">
                      <td>
                        <a href="ShareConfigInfo.aspx?param=<%# Eval("ID").ToString()%>" class="l">编辑</a>
                      </td>
                      <td>
                        <%# Eval( "DayShareLmt" ).ToString( )%>
                      </td>
                        <td>
                        <%# Eval( "TimeShareGold" ).ToString( )%>
                      </td>
                      <td>
                        <%# Eval( "TimeShareDiamond" ).ToString( )%>
                      </td>
                      <td>
                        <%# Eval( "Nullity" ).ToString()=="0"?"启用":"禁用"%>
                      </td>
                    </tr>
                </ItemTemplate>
                <AlternatingItemTemplate>
                    <tr align="center" class="list" onmouseover="currentcolor=this.style.backgroundColor;this.style.backgroundColor='#caebfc';this.style.cursor='default';"
                        onmouseout="this.style.backgroundColor=currentcolor">
                      <td>
                        <a href="ShareConfigInfo.aspx?param=<%# Eval("ID").ToString()%>" class="l">编辑</a>
                      </td>
                      <td>
                        <%# Eval( "DayShareLmt" ).ToString( )%>
                      </td>
                        <td>
                        <%# Eval( "TimeShareGold" ).ToString( )%>
                      </td>
                      <td>
                        <%# Eval( "TimeShareDiamond" ).ToString( )%>
                      </td>
                      <td>
                        <%# Eval( "Nullity" ).ToString()=="0"?"启用":"禁用"%>
                      </td>
                    </tr>
                </AlternatingItemTemplate>
            </asp:Repeater>
            <asp:Literal runat="server" ID="litNoData" Visible="false" Text="<tr class='tdbg'><td colspan='100' align='center'><br>没有任何信息!<br><br></td></tr>"></asp:Literal>
        </table>
    </div>
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
            <td class="listTitleBg"><span>选择：</span>&nbsp;<a class="l1" href="javascript:SelectAll(true);">全部</a>&nbsp;-&nbsp;<a class="l1" href="javascript:SelectAll(false);">无</a></td>
            <td align="right" class="page">
                <gsp:AspNetPager ID="anpNews" runat="server" onpagechanged="anpNews_PageChanged" AlwaysShow="true" FirstPageText="首页" LastPageText="末页" PageSize="20"
                    NextPageText="下页" PrevPageText="上页" ShowBoxThreshold="0" ShowCustomInfoSection="Left" LayoutType="Table" NumericButtonCount="5"
                    CustomInfoHTML="总记录：%RecordCount%　页码：%CurrentPageIndex%/%PageCount%　每页：%PageSize%">
                </gsp:AspNetPager>
            </td>
        </tr>
    </table>
    </form>
</body>
</html>