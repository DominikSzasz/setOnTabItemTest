#include "APIEnvir.h"
#include "ACAPinc.h"

#include "ResourceIds.hpp"
#include "DGModule.hpp"

#include <iostream>

static const GSResID AddOnInfoID			= ID_ADDON_INFO;
	static const Int32 AddOnNameID			= 1;
	static const Int32 AddOnDescriptionID	= 2;

static const short AddOnMenuID				= ID_ADDON_MENU;
	static const Int32 AddOnCommandID		= 1;




class ExampleDialog :
    public DG::ModalDialog,
    public DG::ButtonItemObserver,
    public DG::ListBoxObserver
{
public:
    enum DialogResourceIds {
        ExampleDialogResourceId = ID_ADDON_DLG,
        OKButtonId = 1,
        CancelButtonId = 2,
        TextEditId = 3,
        ItemListId = 4
    };

    ExampleDialog () :
        DG::ModalDialog (ACAPI_GetOwnResModule (), ExampleDialogResourceId, ACAPI_GetOwnResModule ()),
        okButton (GetReference (), OKButtonId),
        cancelButton (GetReference (), CancelButtonId),
        itemList (GetReference (), ItemListId),
        textEdit (GetReference (), TextEditId)
    {
//        Attach (*this);
        okButton.Attach (*this);
        cancelButton.Attach (*this);
        itemList.Attach (*this);

        itemList.SetTabFieldCount (1);
        itemList.SetHeaderItemCount (1);
        itemList.SetTabFieldProperties (1, 0, 100, DG::ListBox::Left, DG::ListBox::EndTruncate);
        itemList.SetHeaderItemText (1, "test");

        for (short i = 1; i <= 3; ++i) {
            itemList.AppendItem ();
            itemList.SetTabItemText (i, 1, "testing");
        }
    }

    ~ExampleDialog () override
    {
        itemList.Detach (*this);
        cancelButton.Detach (*this);
        okButton.Detach (*this);
//        Detach (*this);
    }

private:
    void ButtonClicked (const DG::ButtonClickEvent& ev) override
    {
        if (ev.GetSource () == &okButton)
            PostCloseRequest (DG::ModalDialog::Accept);
        else if (ev.GetSource () == &cancelButton)
            PostCloseRequest (DG::ModalDialog::Cancel);
    }

    void ListBoxSelectionChanged (const DG::ListBoxSelectionEvent& ev) override
    {
        if (ev.GetSource () != &itemList)
            return;

        itemList.RemoveOnTabItem (1);

        const short sel = itemList.GetSelectedItem ();
        if (sel <= 0)
            return;

        textEdit.SetText (itemList.GetTabItemText (sel, 1));
        ACAPI_WriteReport("Before:", false);
        ACAPI_WriteReport("textedit size: " + GS::ValueToUniString(textEdit.GetWidth()) + "x" + GS::ValueToUniString(textEdit.GetHeight()), false);
        ACAPI_WriteReport("listitem size: " + GS::ValueToUniString(itemList.GetTabFieldWidth(1)) + "x" + GS::ValueToUniString(itemList.GetItemHeight()), false);
        
        textEdit.SetWidth(itemList.GetTabFieldWidth(1)-2);
        textEdit.SetHeight(itemList.GetItemHeight()-2);
        
        ACAPI_WriteReport("After:", false);
        ACAPI_WriteReport("textedit size: " + GS::ValueToUniString(textEdit.GetWidth()) + "x" + GS::ValueToUniString(textEdit.GetHeight()), false);
        ACAPI_WriteReport("listitem size: " + GS::ValueToUniString(itemList.GetTabFieldWidth(1)) + "x" + GS::ValueToUniString(itemList.GetItemHeight()), false);
        itemList.SetOnTabItem (1, textEdit);
    }

private:
    DG::Button okButton;
    DG::Button cancelButton;
    DG::SingleSelListBox itemList;
    DG::TextEdit textEdit;
};


static GSErrCode MenuCommandHandler (const API_MenuParams *menuParams)
{
	switch (menuParams->menuItemRef.menuResID) {
		case AddOnMenuID:
			switch (menuParams->menuItemRef.itemIndex) {
				case AddOnCommandID:
					{
						ExampleDialog dialog;
						dialog.Invoke ();
					}
					break;
			}
			break;
	}
	return NoError;
}

API_AddonType CheckEnvironment (API_EnvirParams* envir)
{
	RSGetIndString (&envir->addOnInfo.name, AddOnInfoID, AddOnNameID, ACAPI_GetOwnResModule ());
	RSGetIndString (&envir->addOnInfo.description, AddOnInfoID, AddOnDescriptionID, ACAPI_GetOwnResModule ());

	return APIAddon_Normal;
}

GSErrCode RegisterInterface (void)
{
#ifdef ServerMainVers_2700
	return ACAPI_MenuItem_RegisterMenu (AddOnMenuID, 0, MenuCode_Tools, MenuFlag_Default);
#else
	return ACAPI_Register_Menu (AddOnMenuID, 0, MenuCode_Tools, MenuFlag_Default);
#endif
}

GSErrCode Initialize (void)
{
#ifdef ServerMainVers_2700
	return ACAPI_MenuItem_InstallMenuHandler (AddOnMenuID, MenuCommandHandler);
#else
	return ACAPI_Install_MenuHandler (AddOnMenuID, MenuCommandHandler);
#endif
}

GSErrCode FreeData (void)
{
	return NoError;
}
