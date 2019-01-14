<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="assignment3_2._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">


    <div>
        <asp:Label ID="lblTitle" runat="server" Text="DVD Title"></asp:Label>
        <asp:TextBox ID="txtTitle" runat="server"></asp:TextBox>
    </div>
    <div>
        <asp:Label ID="lbl" runat="server" Text="DVD Description"></asp:Label>
        <asp:TextBox ID="txtDescription" runat="server"></asp:TextBox>
        
    </div>
    <div>
        <asp:Label ID="lblYear" runat="server" Text="DVD Year"></asp:Label>
        <asp:TextBox ID="txtYear" runat="server" TextMode="Number"></asp:TextBox>
        
    </div>
    <div>
        <asp:Button ID="btnAddDVD" runat="server" Text="AddDVD" OnClick="btnAddDVD_Click" />
    </div>
</asp:Content>
