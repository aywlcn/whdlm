﻿using System;
using System.Web.UI.WebControls;

using Game.Utils;
using Game.Kernel;
using Game.Web.UI;
using Game.Facade;
using Game.Entity.Agent;
using Game.Entity.Accounts;

namespace Game.Web.Module.AgentManager
{
    public partial class AgentReturnReceiveList : AdminPage
    {
        /// <summary>
        /// 页面加载
        /// </summary>
        protected void Page_Load(object sender, EventArgs e)
        {
            base.moduleID = 1002;
            if (!IsPostBack)
            {
                ddlAwardType.DataSource = EnumDescription.GetFieldTexts(typeof(AppConfig.AwardType));
                ddlAwardType.DataTextField = "Description";
                ddlAwardType.DataValueField = "EnumValue";
                ddlAwardType.DataBind();
                ddlAwardType.Items.Insert(0, new ListItem("全部返利类型", "0"));

                txtStartDate.Text = DateTime.Now.ToString("yyyy-MM-dd");
                txtEndDate.Text = DateTime.Now.ToString("yyyy-MM-dd");

                BindData();
            }
        }
        /// <summary>
        /// 搜索按钮的功能
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnQuery_Click(object sender, EventArgs e)
        {
            BindData();
        }
        /// <summary>
        /// 数据分页
        /// </summary>
        protected void anpNews_PageChanged(object sender, EventArgs e)
        {
            BindData();
        }
        /// <summary>
        /// 数据绑定
        /// </summary>
        private void BindData()
        {
            string where = "WHERE 1=1";
            string query = CtrlHelper.GetTextAndFilter(txtSearch);
            int awardType = Convert.ToInt32(ddlAwardType.SelectedValue);
            string stime = CtrlHelper.GetTextAndFilter(txtStartDate);
            string etime = CtrlHelper.GetTextAndFilter(txtEndDate);
            if (!string.IsNullOrEmpty(stime) && !string.IsNullOrEmpty(etime))
            {
                where = where + string.Format(" AND CollectDate>='{0}' AND CollectDate<='{1}'", stime + " 00:00:00", etime + " 23:59:59");
            }
            if (!string.IsNullOrEmpty(query))
            {
                if (!Utils.Validate.IsPositiveInt(query))
                {
                    ShowError("输入查询格式不正确");
                    return;
                }
                UserInfo info = FacadeManage.aideAccountsFacade.GetUserInfo(0, Convert.ToInt32(query));
                if (info != null)
                {
                    where = where + string.Format(" AND UserID={0}", info.UserID);
                }
            }
            if (awardType > 0)
            {
                where = where + string.Format(" AND AwardType = {0}", awardType);
            }

            PagerSet pagerSet = FacadeManage.aideAgentFacade.GetList(ReturnAwardReceive.Tablename, where, "ORDER BY CollectDate DESC", anpNews.CurrentPageIndex, anpNews.PageSize);
            anpNews.RecordCount = pagerSet.RecordCount;
            if (pagerSet.RecordCount > 0)
            {
                rptDataList.DataSource = pagerSet.PageSet;
                rptDataList.DataBind();
            }
            litNoData.Visible = pagerSet.RecordCount <= 0;
            rptDataList.Visible = pagerSet.RecordCount > 0;
        }
    }
}