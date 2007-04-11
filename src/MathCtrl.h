///
///  Copyright (C) 2004-2007 Andrej Vodopivec <andrejv@users.sourceforge.net>
///
///  This program is free software; you can redistribute it and/or modify
///  it under the terms of the GNU General Public License as published by
///  the Free Software Foundation; either version 2 of the License, or
///  (at your option) any later version.
///
///  This program is distributed in the hope that it will be useful,
///  but WITHOUT ANY WARRANTY; without even the implied warranty of
///  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///  GNU General Public License for more details.
///
///
///  You should have received a copy of the GNU General Public License
///  along with this program; if not, write to the Free Software
///  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
///

#ifndef _MATHCTRL_H_
#define _MATHCTRL_H_

#include <wx/wx.h>

#include "MathCell.h"

enum {
  popid_copy,
  popid_cut,
  popid_paste,
  popid_select_all,
  popid_copy_text,
  popid_copy_image,
  popid_delete,
  popid_simplify,
  popid_expand,
  popid_factor,
  popid_solve,
  popid_solve_num,
  popid_integrate,
  popid_diff,
  popid_subst,
  popid_plot2d,
  popid_plot3d,
  popid_float,
  popid_edit,
  popid_reeval,
  popid_add_comment,
  popid_insert_input,
  popid_copy_tex,
#if defined __WXMSW__
  popid_image_copy,
#endif
  popid_image,
  popid_comment,
  popid_uncomment
};

class MathCtrl: public wxScrolledWindow
{
public:
  MathCtrl(wxWindow* parent, int id, wxPoint pos, wxSize size);
  ~MathCtrl();
  void DestroyTree();
  void DestroyTree(MathCell* tree);
  MathCell* CopyTree();
  void AddLine(MathCell *newLine, bool forceNewLine = false);
  void InsertLine(MathCell *newLine, bool forceNewLine = false);
  void Recalculate(bool scroll = true);
  void RecalculateForce();
  void Recalculate(MathCell *cell, bool scroll = true);
  void RecalculateWidths();
  void RecalculateWidths(MathCell *cell);
  void RecalculateSize();
  void RecalculateSize(MathCell *cell);
  void ClearWindow();
  bool CanCopy(bool fromActive = false)
  {
    return m_selectionStart != NULL ||
           (fromActive && m_activeCell != NULL && m_activeCell->CanCopy());
  }
  bool CanPaste()
  {
    return m_activeCell != NULL;
  }
  bool CanCut()
  {
    return m_activeCell != NULL && m_activeCell->CanCopy();
  }
  void SelectAll();
  bool CanDeleteSelection();
  bool CanAddComment();
  bool CanAddInput();
  void DeleteSelection(bool deletePrompt = true);
  bool CutToClipboard();
  void PasteFromClipboard();
  bool Copy(bool lb = false);
  bool CopyTeX();
  bool CopyBitmap();
  bool CopyToFile(wxString file);
  bool CopyToFile(wxString file, MathCell* start, MathCell* end, bool asData = false);
  bool ExportToHTML(wxString file);
  bool ExportToMAC(wxString file);
  wxString GetString(bool lb = false);
  MathCell* GetTree()
  {
    return m_tree;
  }
  void BreakUpCells();
  void BreakUpCells(MathCell *cell);
  void UnBreakUpCells();
  MathCell* GetLastCell();
  MathCell* GetLastPrompt();
  void SetInsertPoint(MathCell* insert)
  {
    m_insertPoint = insert;
  }
  MathCell* GetInsertPoint()
  {
    return m_insertPoint;
  }
  void ClearInsertPoint()
  {
    m_insertPoint = NULL;
  }
  MathCell* GetSelectionStart()
  {
    return m_selectionStart;
  }
  void SetSelection(MathCell* sel)
  {
    m_selectionStart = m_selectionEnd = sel;
  }
  void SetScrollTo(int to)
  {
    m_scrollTo = to;
  }
  bool CanEdit();
  void EnableEdit(bool enable = true)
  {
    m_editingEnabled = enable;
  }
  void UnfoldAll();
  bool SelectPrevInput();
  bool SelectNextInput();
  bool SelectPrompt();
  void ScrollToSelectionStart();
  bool SelectLastInput();
  void SetActiveCell(MathCell *cell);
  MathCell* GetActiveCell()
  {
    return m_activeCell;
  }
  void ShowPoint(wxPoint point);
  void OnSetFocus(wxFocusEvent& event);
  void OnKillFocus(wxFocusEvent& event);
protected:
  MathCell* CopySelection();
  MathCell* CopySelection(MathCell* start, MathCell* end, bool asData = false);
  void GetMaxPoint(int* width, int* height);
  void BreakLines(MathCell* cell);
  void OnTimer(wxTimerEvent& event);
  void OnMouseExit(wxMouseEvent& event);
  void OnMouseEnter(wxMouseEvent& event);
  void OnPaint(wxPaintEvent& event);
  void OnSize(wxSizeEvent& event);
  void OnMouseRightUp(wxMouseEvent& event);
  void OnMouseLeftUp(wxMouseEvent& event);
  void OnMouseLeftDown(wxMouseEvent& event);
  void OnMouseMotion(wxMouseEvent& event);
  void OnDoubleClick(wxMouseEvent& event);
  void OnKeyDown(wxKeyEvent& event);
  void OnChar(wxKeyEvent& event);
  void SelectPoint(wxPoint& point);
  void SelectRect(wxPoint one, wxPoint two);
  void AdjustSize(bool scroll = false);
  void OnEraseBackground(wxEraseEvent& event)
  { }
  void InsertAfter(MathCell *insertPoint, MathCell *newCell, bool forceBreakLine);
  void CheckUnixCopy();
  wxPoint m_down;
  wxPoint m_up;
  wxPoint m_mousePoint;
  bool m_leftDown;
  bool m_mouseDrag;
  bool m_selectWholeLine;
  bool m_mouseOutside;
  bool m_forceUpdate;
  MathCell *m_tree;
  MathCell *m_last;
  MathCell *m_firstVisible;
  MathCell *m_lastVisible;
  MathCell *m_selectionStart;
  MathCell *m_selectionEnd;
  MathCell *m_insertPoint;
  MathCell *m_activeCell;
  CellParser *m_selectionParser;
  bool m_switchDisplayCaret;
  bool m_editingEnabled;
  int m_scrollTo;
  wxTimer m_timer, m_caretTimer;
  wxBitmap *m_memory;
  DECLARE_EVENT_TABLE()
};

#endif //_MATHCTRL_H_
