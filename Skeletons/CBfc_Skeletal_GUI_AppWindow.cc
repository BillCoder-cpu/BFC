
#include <BFCGUI.h>

// CBfc_Skeletal_GUI_AppWindow.cc
//
class CBfc_Skeletal_GUI_AppWindow : public CBfcGUI_Window
{
public:
  CBfc_Skeletal_GUI_AppWindow (CBfcGUI &GUI, CBfcGUI_Resource_ID resourceID);  // Constructor - takes a bfc resource ID.

protected:  // try to get away with this.

// These are optional virtual functions that the base clas will handle.
//    virtual int onKeyUp ();
//    virtual int onKeyDown ();

//    virtual int onMouseMove ();  // This is an override so we get control of the main window.
//    virtual int onMouseUp ();    //
//    virtual int onMouseDown ();  //
//    virtual int onMouseDoubleClick ();    // etc.

    virtual int onMessage ();
};

#define RESOURCE_FILENAME STATICBYTES("Skeletal_GUI.bfcres")

// Skeletal main function
main (int argc, char *argv[])
{
   const bool b_ReadOnly = true;
    CBfc_Stream		    resourceStream(CBfc_Filename(characterPtr(RESOURCE_FILENAME)));
   CBfcGUI_ScriptResource   resource(resourceStream);
   CBfcGUI      	    GUI(&resource);        // There can be several running at once.

   CBfc_Skeletal_GUI_AppWindow    	Mainwindow(GUI,RES_WINDOW_MAIN);    // This should be derived from CBfcGUI_Window

   bool bOk = GUI.LaunchGUI (MainWindow);    // Starts up our Gui - messages become active when things happen.
   return (bOK ? 0:1);
}

CBfc_Skeletal_GUI_AppWindow::CBfc_Skeletal_GUI_AppWindow (CBfcGUI_Resource_ID resourceID)
{
}

int CBfc_Skeletal_GUI_AppWindow::onMessage ()
{
  return BFCGUIDEFS_MESSAGE_NOT_PROCESSED;
}








