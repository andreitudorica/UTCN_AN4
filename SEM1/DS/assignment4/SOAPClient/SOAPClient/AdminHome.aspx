<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AdminHome.aspx.cs" Inherits="SOAPClient.AdminHome" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Admin Home</title>
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

                        <asp:TemplateField>
                            <ItemTemplate>
                                <asp:LinkButton ID="lnkRemove" runat="server" CommandArgument='<%# Bind("Name")%>' OnClientClick="return confirm ('Are you sure you want to remove this?')"
                                    Text="Remove" OnClick="RemovePackage"></asp:LinkButton>
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
            <asp:LinkButton ID="lbtnAdd" runat="server" OnClick="lbtnAdd_Click">AddNew</asp:LinkButton>


            <asp:Panel ID="pnlAdd" runat="server" Visible="False">
                <div>
                    Sender name: 
                <asp:TextBox ID="txtSender" runat="server"></asp:TextBox>
                </div>
                <div>
                    Receiver name: 
                <asp:TextBox ID="txtReceiver" runat="server"></asp:TextBox>
                </div>
                <div>
                    Name: 
                <asp:TextBox ID="txtName" runat="server"></asp:TextBox>
                </div>
                <div>
                    Description: 
                <asp:TextBox ID="txtDescription" runat="server"></asp:TextBox>
                </div>
                <div>
                    Sender city: 
                <asp:TextBox ID="txtSenderCity" runat="server"></asp:TextBox>
                </div>
                <div>
                    Destination city: 
                <asp:TextBox ID="txtDestinationCity" runat="server"></asp:TextBox>
                </div>
                <div>
                    <asp:LinkButton ID="lbtnSubmit" runat="server" OnClick="lbtnSubmit_Click">Submit</asp:LinkButton>

                    <asp:LinkButton ID="lbtnCancel" runat="server" OnClick="lbtnCancel_Click">Cancel</asp:LinkButton>
                </div>

            </asp:Panel>
        </div>
        <div>
            <asp:LinkButton ID="btnStartTrackingPanel" runat="server" OnClick="btnStartTrackingPanel_Click">Start Tracking a package</asp:LinkButton>


            <asp:Panel ID="pnlStartTracking" runat="server" Visible="False">
                <div>
                    Package name: 
                <asp:TextBox ID="txtPackageName" runat="server"></asp:TextBox>
                </div>
                <div>
                    <asp:LinkButton ID="lnkStartTracking" runat="server" OnClick="lnkStartTracking_Click">Start Tracking</asp:LinkButton>

                    <asp:LinkButton ID="lnkStartTrackingCancel" runat="server" OnClick="lnkStartTrackingCancel_Click">Cancel</asp:LinkButton>
                </div>

            </asp:Panel>
        </div>

        <div>
            <asp:LinkButton ID="btnAddCityPanel" runat="server" OnClick="btnAddCityPanel_Click">Add City to route</asp:LinkButton>


            <asp:Panel ID="pnlAddCity" runat="server" Visible="False">
                <div>
                    Package name: 
                <asp:TextBox ID="txtPackage" runat="server"></asp:TextBox>
                </div>
                <div>
                    City name and date: 
                <asp:TextBox ID="txtCity" runat="server"></asp:TextBox>
                </div>
                <div>
                    <asp:LinkButton ID="btnAddCity" runat="server" OnClick="btnAddCity_Click">Add City</asp:LinkButton>

                    <asp:LinkButton ID="btnCancelCity" runat="server" OnClick="btnCancelCity_Click">Cancel</asp:LinkButton>
                </div>

            </asp:Panel>
        </div>
    </form>
</body>
</html>
