// -*- c++ -*-
// Generated by gtkmmproc -- DO NOT MODIFY!
#ifndef _GTKMM_TARGETLIST_H
#define _GTKMM_TARGETLIST_H

#include <glibmm.h>

/* Copyright(C) 2002 The gtkmm Development Team
 *
 * This library is free software, ) you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation, ) either
 * version 2 of the License, or(at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, ) without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library, ) if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#include <gtkmm/enums.h>
#include <gtkmm/targetentry.h>
#include <gdkmm/types.h>


namespace Gtk
{

class TargetList
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef TargetList CppObjectType;
  typedef GtkTargetList BaseObjectType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


  // For use with Glib::RefPtr<> only.
  void reference()   const;
  void unreference() const;

  ///Provides access to the underlying C instance.
  GtkTargetList*       gobj();

  ///Provides access to the underlying C instance.
  const GtkTargetList* gobj() const;

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GtkTargetList* gobj_copy() const;

protected:
  // Do not derive this.  Gtk::TargetList can neither be constructed nor deleted.
  TargetList();
  void operator delete(void*, size_t);

private:
  // noncopyable
  TargetList(const TargetList&);
  TargetList& operator=(const TargetList&);


public:
  static Glib::RefPtr<Gtk::TargetList> create(const ArrayHandle_TargetEntry& targets);
  
 
  void add(const Glib::ustring& target, TargetFlags flags = TargetFlags(0), guint info = 0);
  void add(const ArrayHandle_TargetEntry& targets);
  
  void remove(const Glib::ustring& target);
  
  bool find(const Glib::ustring& target, guint* info) const;


};

} // namespace Gtk


namespace Glib
{

  /** @relates Gtk::TargetList
   * @param object The C instance
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   */
  Glib::RefPtr<Gtk::TargetList> wrap(GtkTargetList* object, bool take_copy = false);

} // namespace Glib

#endif /* _GTKMM_TARGETLIST_H */
