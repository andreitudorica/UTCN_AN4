<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ClientHome.aspx.cs" Inherits="SOAPClient.ClientHome" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form runat="server">
        <asp:Button ID="btnLogOut" runat="server" Text="Log out" OnClick="btnLogOut_Click" />
        <asp:ScriptManager EnablePartialRendering="true"
            ID="ScriptManager1" runat="server">
        </asp:ScriptManager>
        <asp:UpdatePanel ID="UpdatePanel1" runat="server">
            <ContentTemplate>
                <asp:GridView ID="gvPackage" runat="server" AutoGenerateColumns="False" BackColor="White"
                    BorderColor="#3366CC" BorderStyle="None" BorderWidth="1px" CellPadding="4">
                    <RowStyle BackColor="White" ForeColor="#003399" />
                    <Columns>

                        <asp:TemplateField HeaderText="Sender">
                            <ItemTemplate>
                                <asp:Label ID="lblSender" runat="server" Text='<%# Bind("Sender") %>'></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateField>

                        <asp:TemplateField HeaderText="Receiver">
                            <ItemTemplate>
                                <asp:Label ID="lblReceiver" runat="server" Text='<%# Bind("Receiver") %>'></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateField>

                        <asp:TemplateField HeaderText="Name">
                            <ItemTemplate>
                                <asp:Label ID="lblName" runat="server" Text='<%# Bind("Name") %>'></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateField>

                        <asp:TemplateField HeaderText="Description">
                            <ItemTemplate>
                                <asp:Label ID="lblDescription" runat="server" Text='<%# Bind("Description") %>'></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateField>

                        <asp:TemplateField HeaderText="Sender City">
                            <ItemTemplate>
                                <asp:Label ID="lblSenderCity" runat="server" Text='<%# Bind("SenderCity") %>'></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateField>

                        <asp:TemplateField HeaderText="Receiver City">
                            <ItemTemplate>
                                <asp:Label ID="lblDestinationCity" runat="server" Text='<%# Bind("DestinationCity") %>'></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateField>


                        <asp:TemplateField HeaderText="Is Tracked">
                            <ItemTemplate>
                                <asp:Label ID="lblisTracked" runat="server" Text='<%# Bind("isTracked") %>'></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateField>

                        <asp:TemplateField HeaderText="Route">
                            <ItemTemplate>
                                <asp:Label ID="Tracking" runat="server" Text='<%# Bind("Tracking") %>'></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateField>

                    </Columns>
                    <FooterStyle BackColor="#99CCCC" ForeColor="#003399" />
                    <PagerStyle BackColor="#99CCCC" ForeColor="#003399" HorizontalAlign="Left" />
                    <SelectedRowStyle BackColor="#009999" Font-Bold="True" ForeColor="#CCFF99" />
                    <HeaderStyle BackColor="#003399" Font-Bold="True" ForeColor="#CCCCFF" />
                </asp:GridView>
            </ContentTemplate>
        </asp:UpdatePanel>
         <div>
                    Search name: 
                <asp:TextBox ID="txtSearch" runat="server"></asp:TextBox>
                </div>
                    <asp:LinkButton ID="lbtnSubmit" runat="server" OnClick="lbtnSearch_Click">Submit</asp:LinkButton>
                    <asp:LinkButton ID="LinkButton1" runat="server" OnClick="lbtnRebind_Click">All packages</asp:LinkButton>

    </form>
</body>
</html>
