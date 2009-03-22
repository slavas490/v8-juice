#if !defined(CODE_GOOGLE_COM_P_V8JUICE_PLUGIN_NCURSES_H_INCLUDED)
#define CODE_GOOGLE_COM_P_V8JUICE_PLUGIN_NCURSES_H_INCLUDED 1
/**
   Implementation code for v8 (JavaScript engine) bindings for sqlite3.

   v8: http://code.google.com/p/v8/

   sqlite3: http://sqlite.org

   Author: Stephan Beal (http://wanderinghorse.net/home/stephan/)

   License: same as v8 (see below)
*/
// Copyright 2007-2009 Stephan Beal. All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Google Inc. nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "ncwindow.hpp"
#include "ncpanel.hpp"

#include <v8/juice/WeakJSClassCreator.h>

namespace v8 { namespace juice {
/**
   The v8::juice::nc namespace encapsulates ncurses bindings for
   v8. Call v8::juice::nc::SetupAddon() to install the ncurses API into
   an existing JS object (normally the global object). Functions in
   the native API marked with the V8_NCURSES_BINDING macro represent
   JS-side functions made available by this addon (and no native
   implementations exist using those names, so don't try to call them
   from native code).
*/
namespace nc {

    /**
       kludge to work around an uncertain type size:
       chtype is defined in ncurses.h, but we're going
       to shadow it for CastTo/FromJS() purposes.
    */
    typedef uint32_t chtype;

    using namespace ::ncutil;

    class JWidgetBase
    {
    public:
        JWidgetBase()
        {}
        virtual ~JWidgetBase() {}

    };


    class JWindow : private NCMode,
                    public JWidgetBase
    {
    public:
        NCWindow * ncwin;
        JWindow()
        {}
        virtual ~JWindow()
        {
            if( this->ncwin ) delete this->ncwin;
        }
        static Persistent<Function> js_ctor;

        std::string name() const { return ncwin->name(); }
        void name( std::string n ) { ncwin->name(n); }

        int lines() { return ncwin->lines(); }
        int cols() { return ncwin->cols(); }
        int tabsize() { return ncwin->tabsize(); }
        int height() { return ncwin->height(); }
        int width() { return ncwin->width(); }
        int begy() { return ncwin->begy(); }
        int begx() { return ncwin->begx(); }
        int maxx() { return ncwin->maxx(); }
        int maxy() { return ncwin->maxy(); }
        chtype inch() { return ncwin->inch(); }
        int insertln() { return ncwin->insertln(); }
        chtype getbkgd() { return ncwin->getbkgd(); }
        int erase() { return ncwin->erase(); }
        int clear() { return ncwin->clear(); }
        int clrtobot() { return ncwin->clrtobot(); }
        int delch() { return ncwin->delch(); }
        int deleteln() { return ncwin->deleteln(); }
        int touchwin() { return ncwin->touchwin(); }
        int untouchwin() { return ncwin->untouchwin(); }
        bool is_wintouched() { return ncwin->is_wintouched(); }
        int redrawwin() { return ncwin->redrawwin(); }
        int doupdate() { return ncwin->doupdate(); }
        void syncdown() { return ncwin->syncdown(); }
        void syncup() { return ncwin->syncup(); }
        void cursyncup() { return ncwin->cursyncup(); }
        int standout() { return ncwin->standout(); }
        int standend() { return ncwin->standend(); }
        int refresh() { return ncwin->refresh(); }
        int noutrefresh() { return ncwin->noutrefresh(); }
        bool has_mouse() { return ncwin->has_mouse(); }

        int insch(chtype v) { return ncwin->insch(v); }
        int insdelln(int v) { return ncwin->insdelln(v); }
        int insstr(std::string v) { return ncwin->insstr(v.c_str()); }
        int attron(chtype v) { return ncwin->attron(v); }
        int attroff(chtype v) { return ncwin->attroff(v); }
        int attrset(chtype v) { return ncwin->attrset(v); }
        int color_set(short v) { return ncwin->color_set(v); }
        int bkgd(chtype v) { return ncwin->bkgd(v); }
        int clearok(bool v) { return ncwin->clearok(v); }
        int scroll(int v) { return ncwin->scroll(v); }
        int scrollok(bool v) { return ncwin->scrollok(v); }
        int idlok(bool v) { return ncwin->idlok(v); }
        void idcok(bool v) { ncwin->idcok(v); }
        int leaveok(bool v) { return ncwin->leaveok(v); }
        void immedok(bool v) { return ncwin->immedok(v); }
        int keypad(bool v) { return ncwin->keypad(v); }
        int addch(chtype v) { return ncwin->addch(v); }
        int echochar(chtype v) { return ncwin->echochar(v); }
        int addstr(std::string v) { return ncwin->addstr(v.c_str()); }
        bool is_linetouched(int v) { return ncwin->is_linetouched(v); }

        int mvwin(int v1,int v2) { return ncwin->mvwin(v1,v2); }
        int move(int v1,int v2) { return ncwin->move(v1,v2); }
        int getch(int v1,int v2) { return ncwin->getch(v1,v2); }
        int addstrn(std::string v1,int v2) { return ncwin->addstr(v1.c_str(),v2); }
        chtype mvinch(int v1,int v2) { return ncwin->inch(v1,v2); }
        int insstrn(std::string v1,int v2) { return ncwin->insstr(v1.c_str(),v2); }
        int mvdelch(int v1,int v2) { return ncwin->delch(v1,v2); }
        int setscrreg(int v1,int v2) { return ncwin->setscrreg(v1,v2); }
        int touchln(int v1,int v2) { return ncwin->touchln(v1,v2); }
        int redrawln(int v1,int v2) { return ncwin->redrawln(v1,v2); }

        int mvinsstr(int v1,int v2,std::string v3) { return ncwin->insstr(v1,v2,v3.c_str()); }
        int mvaddch(int v1,int v2,chtype v3) { return ncwin->addch(v1,v2,v3); }
        int mvaddstr(int v1, int v2, std::string v3) { return ncwin->addstr(v1,v2,v3.c_str()); }
        int mvinsch(int v1,int v2,chtype v3) { return ncwin->insch(v1,v2,v3); }

        int mvaddstrn(int v1, int v2, std::string v3,int v4) { return ncwin->addstr(v1,v2,v3.c_str(),v4); }
        int mvinsstrn(int v1,int v2,std::string v3,int v4) { return ncwin->insstr(v1,v2,v3.c_str(),v4); }
        int mvcur(int v1,int v2,int v3,int v4) { return ncwin->mvcur(v1,v2,v3,v4); }
    };

    class JPanel : public JWidgetBase
    {
        NCPanel * ncwin;
        JPanel()
        {}
        virtual ~JPanel()
        {}
    };

    class JPad : public JWidgetBase // JWindow?
    {
    };

    enum { library_version = 0x20090322 };


    /**
       Common WeakJSClassCreatorOps impl for JWindow and friends.
    */
    template <typename WrappedT,
              char const * &className,
              WrappedT * (*ctor_proxy)( Arguments const &, std::string & exceptionText ),
              void (*dtor_proxy)( WrappedT * )
        >
    struct BaseWeakOps
    {
        typedef WrappedT WrappedType;
        enum { ExtraInternalFieldCount = 0 };
        static char const * ClassName() { return className; }
        static WrappedType * Ctor( Arguments const & argv, std::string & exceptionText )
        {
            WrappedType * x = ctor_proxy(argv,exceptionText);
            if( x )
            {
                cleanup::AddToCleanup( x, cleanup_callback );
            }
            return x;
        }

        static void Dtor( WrappedType * obj )
        {
            cleanup::RemoveFromCleanup( obj );
            dtor_proxy( obj );
        }
    private:
        static void cleanup_callback( void * obj )
        {
            Dtor( static_cast<WrappedType *>( obj ) );
        }

    };

    struct strings
    {
        // Class names:
        static const char * classWindow;
        static const char * classPanel;
        static const char * classPad;

        // Function names:
        static const char * fClose;
        static const char * fEndwin;
        static const char * fGetch;
        static const char * fName;
        static const char * fNameSet;
    };

    JWindow * window_ctor( Arguments const & argv, std::string & exceptionText );
    void window_dtor( JWindow * w );

} /* namespaces */

    template <>
    struct WeakJSClassCreatorOps< nc::JWindow >
        : nc::BaseWeakOps< nc::JWindow,
                           nc::strings::classWindow,
                           nc::window_ctor,
                           nc::window_dtor
                           >
    {
    };

//     template <>
//     struct WeakJSClassCreatorOps< JPanel >;
//     template <>
//     struct WeakJSClassCreatorOps< JPad >;

}} /* namespaces */

#define WEAK_CLASS_TYPE v8::juice::nc::JWindow
#include <v8/juice/WeakJSClassCreator-CastOps.h>

#endif /* CODE_GOOGLE_COM_P_V8JUICE_PLUGIN_NCURSES_H_INCLUDED */