<%@ Page Title="About" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="About.aspx.cs" Inherits="ClientWeb.About" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <asp:Label ID="Label1" runat="server" Text="Year"></asp:Label>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <asp:TextBox ID="txtYear" runat="server" TextMode="Number"></asp:TextBox>
    <br />
    <asp:Label ID="Label2" runat="server" Text="Engine Size"></asp:Label>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <asp:TextBox ID="txtEngineSize" runat="server" TextMode="Number"></asp:TextBox>
    <br />
    <asp:Label ID="Label3" runat="server" Text="Purchasing Price"></asp:Label>
&nbsp;&nbsp;&nbsp;&nbsp;
    <asp:TextBox ID="txtPurchasingPrice" runat="server" TextMode="Number"></asp:TextBox>
&nbsp;LEI<br />
    <asp:Button ID="btnCompute" runat="server" OnClick="btnCompute_Click" Text="GO" />
    <br />
    <asp:Label ID="lblTax" runat="server" Text="Tax: "></asp:Label>
    <br />
    <asp:Label ID="lblSellingPrice" runat="server" Text="Selling Price:"></asp:Label>
    <br />
    <asp:Label ID="lblError" runat="server" BorderWidth="1px" ForeColor="Red" Text="Label" Visible="False"></asp:Label>
</asp:Content>
