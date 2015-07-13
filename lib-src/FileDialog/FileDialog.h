/**********************************************************************

  Audacity: A Digital Audio Editor

  FileDialog.h

  Leland Lucius

*******************************************************************//**

\class FileDialog
\brief Dialog used to present platform specific "Save As" dialog with
custom controls.

*//*******************************************************************/

#ifndef _FILE_DIALOG_H_
#define _FILE_DIALOG_H_

#include <wx/defs.h>
#include <wx/filectrl.h>
#include <wx/filedlg.h>

typedef void (*fdCallback)(void *, int);

/////////////////////////////////////////////////////////////////////////////
// Name:        filedlg.h
// Purpose:     wxFileDialog base header
// Author:      Robert Roebling
// Modified by: Leland Lucius
// Created:     8/17/99
// Copyright:   (c) Robert Roebling
// RCS-ID:      $Id: FileDialog.h,v 1.9 2008-05-24 02:57:39 llucius Exp $
// Licence:     wxWindows licence
//
// Modified for Audacity to support an additional button on Save dialogs
//
/////////////////////////////////////////////////////////////////////////////

#define FD_NO_ADD_EXTENSION 0x0400

class FileDialogBase : public wxFileDialogBase
{
public:
   FileDialogBase();
   virtual ~FileDialogBase() {};

   // FileDialogBase

   typedef void (*UserPaneCreatorFunction)(wxWindow *parent, wxUIntPtr userdata);

   virtual bool HasUserPaneCreator() const;
   virtual void SetUserPaneCreator(UserPaneCreatorFunction creator, wxUIntPtr userdata);

protected:
   void CreateUserPane(wxWindow *parent);

   UserPaneCreatorFunction m_creator;
   wxUIntPtr m_userdata;

   wxString m_buttonlabel;
   fdCallback m_callback;
   void *m_cbdata;
};

#if defined(__WXGTK__)
#include "gtk/FileDialog.h"
#elif defined(__WXMAC__)
#include "mac/FileDialog.h"
#elif defined(__WXMSW__)
#include "win/FileDialogPrivate.h"
#else
#error Unknown implementation
#endif

//----------------------------------------------------------------------------
// FileDialog convenience functions
//----------------------------------------------------------------------------

wxString 
FileSelector(const wxString & message = wxFileSelectorPromptStr,
             const wxString & default_path = wxEmptyString,
             const wxString & default_filename = wxEmptyString,
             const wxString & default_extension = wxEmptyString,
             const wxString & wildcard = wxFileSelectorDefaultWildcardStr,
             int flags = 0,
             wxWindow *parent = NULL);

#endif

