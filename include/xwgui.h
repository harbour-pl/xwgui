#ifndef XWGUI_H
#define XWGUI_H

#include <stddef.h>

#include "xwgui-inkey.h"

#ifdef __cplusplus
extern "C"
{
#endif


/* ---------------------------------------------------------------------------------------------
   Definicje
   --------------------------------------------------------------------------------------------- */

/* Funkcje biblioteki DLL: przy budowie XWGUI (XWGUI_BUILD) eksportowane, w programie importowane; poza Windows bez
   znaczenia */
#if defined( _WIN32 ) && defined( XWGUI_BUILD )
   #define XWGUI_API __declspec( dllexport )
#elif defined( _WIN32 )
   #define XWGUI_API __declspec( dllimport )
#else
   #define XWGUI_API
#endif

/* Kształt kursora tekstowego dla Set( SET_CURSOR, ... ) */
#define SC_NONE       "0"   /* brak */
#define SC_NORMAL     "1"   /* podkreślenie */
#define SC_INSERT     "2"   /* dolna połowa pola */
#define SC_SPECIAL1   "3"   /* pełne pole */
#define SC_SPECIAL2   "4"   /* górna połowa pola */

/* Grubość czcionki dla SvgText() */
#define FONT_WEIGHT_THIN        100
#define FONT_WEIGHT_EXTRA_LIGHT 200
#define FONT_WEIGHT_LIGHT       300
#define FONT_WEIGHT_NORMAL      400
#define FONT_WEIGHT_MEDIUM      500
#define FONT_WEIGHT_SEMI_BOLD   600
#define FONT_WEIGHT_BOLD        700
#define FONT_WEIGHT_EXTRA_BOLD  800
#define FONT_WEIGHT_BLACK       900

/* Wyrównanie tekstu dla SvgText() */
#define SVG_ALIGN_LEFT          0
#define SVG_ALIGN_CENTER        1
#define SVG_ALIGN_RIGHT         2

/* ---------------------------------------------------------------------------------------------
   Typy
   --------------------------------------------------------------------------------------------- */

/* Typ logiczny wspólny z xRDD; program może dołączyć oba nagłówki */
#ifndef XBOOL_DEFINED
   #define XBOOL_DEFINED
   typedef enum xBool
   {
      F = 0,
      T = ( ! 0 )
   } xBool;
#endif

typedef struct App App;
typedef struct Win Win;
typedef struct Svg Svg;
typedef struct Menu Menu;
typedef struct StatusBar StatusBar;
typedef struct Sidebar Sidebar;
typedef struct Picture Picture;
typedef struct Control Control;
typedef struct Timer Timer;
typedef struct TreeItem TreeItem;
typedef struct Toolbar Toolbar;

/* Akcja przycisku paska: pasek i dane podane w ToolbarAdd() */
typedef void ( *ToolbarAction )( Toolbar *toolbar, void *data );

/* Krawędź okna, przy której stoi pasek przycisków */
#define TOOLBAR_TOP    0
#define TOOLBAR_BOTTOM 1
#define TOOLBAR_LEFT   2
#define TOOLBAR_RIGHT  3

/* Kolory paska przycisków dla ToolbarSetColor() */
#define TOOLBAR_FOREGROUND      0
#define TOOLBAR_BACKGROUND      1
#define TOOLBAR_HOVERFOREGROUND 2
#define TOOLBAR_HOVERBACKGROUND 3
#define TOOLBAR_PRESSFOREGROUND 4
#define TOOLBAR_PRESSBACKGROUND 5

/* Akcja kontrolki (klik przycisku, zmiana pola wyboru): kontrolka i dane podane w ControlSetAction() */
typedef void ( *ControlAction )( Control *control, void *data );

/* Akcja timera: timer i dane podane w TimerCreate() */
typedef void ( *TimerAction )( Timer *timer, void *data );

/* Sprawdzenie pola, gdy traci fokus: F zatrzymuje fokus w polu */
typedef xBool ( *ControlValid )( Control *control, void *data );

/* Akcja przycisku paska bocznego: pasek i dane podane przy dodaniu przycisku */
typedef void ( *SidebarAction )( Sidebar *sidebar, void *data );

/* Akcja wiersza listy paska bocznego albo jego przycisku ustawień: pasek, numer wiersza od 1 i dane podane razem
   z akcją */
typedef void ( *SidebarItemAction )( Sidebar *sidebar, int item, void *data );

/* Akcja pozycji menu: okno z menu i dane podane w MenuAdd() */
typedef void ( *MenuAction )( Win *win, void *data );

/* Tabela rekordów jak TBrowse: dane czyta przez akcje programu, które dostają tabelę i dane podane razem z nimi;
   goTop i goBottom ustawiają pierwszy i ostatni rekord, skip przesuwa rekord o count i zwraca, o ile przesunął,
   position zwraca miejsce rekordu 0..1 (ujemne, gdy go nie zna), empty T dla danych bez rekordów */
typedef void ( *BrowseMove )( Control *browse, void *data );
typedef int ( *BrowseSkip )( Control *browse, int count, void *data );
typedef double ( *BrowsePosition )( Control *browse, void *data );
typedef xBool ( *BrowseEmpty )( Control *browse, void *data );

/* Wartość kolumny tabeli w bieżącym rekordzie: tekst (tabela robi sobie kopię), liczba albo znacznik; setCheck daje
   znacznikowi przeciwną wartość */
typedef const char *( *BrowseText )( Control *browse, void *data );
typedef double ( *BrowseNumber )( Control *browse, void *data );
typedef xBool ( *BrowseCheck )( Control *browse, void *data );
typedef void ( *BrowseSetCheck )( Control *browse, xBool value, void *data );

/* Wyrównanie kolumny tabeli */
#define BROWSE_LEFT   0
#define BROWSE_RIGHT  1
#define BROWSE_CENTER 2

/* Kolory tabeli dla BrowseSetColor() */
#define BROWSE_HEADBACKGROUND      0
#define BROWSE_HEADFOREGROUND      1
#define BROWSE_HEADLINE            2
#define BROWSE_BACKGROUND          3
#define BROWSE_ALTERNATEBACKGROUND 4
#define BROWSE_FOREGROUND          5
#define BROWSE_GRIDLINE            6
#define BROWSE_CURSORBACKGROUND    7
#define BROWSE_CURSORFOREGROUND    8
#define BROWSE_INACTIVECURSOR      9
#define BROWSE_CHECKFOREGROUND     10
#define BROWSE_COLORS              11

/* Akcja okna: po zmianie rozmiaru albo pod klawiszem z WinSetKey(); okno i dane podane razem z akcją */
typedef void ( *WinAction )( Win *win, void *data );

/* Zgoda na zamknięcie okna: F zostawia okno otwarte */
typedef xBool ( *WinValid )( Win *win, void *data );

typedef enum
{
   SET_DATEFORMAT,
   SET_PATH,
   SET_CURSOR,
} SetSys;

typedef enum
{
   WIN_NORMAL,
   WIN_MAXIMIZED,
   WIN_MINIMIZED,
   WIN_FULLSCREEN
} WinState;

/* ---------------------------------------------------------------------------------------------
   App
   --------------------------------------------------------------------------------------------- */

XWGUI_API App *AppCreate( void );
XWGUI_API int  AppRun( App *app, Win *win );
XWGUI_API void AppDestroy( App *app );
XWGUI_API const char *AppArg( int index );

/* ---------------------------------------------------------------------------------------------
   Win
   --------------------------------------------------------------------------------------------- */

XWGUI_API Win *WinCreate( App *app, const char *title, int width, int height );
XWGUI_API void WinSetBackground( Win *win, int color );
XWGUI_API int  WinBackground( Win *win );
XWGUI_API void WinSetForeground( Win *win, int color );
XWGUI_API int  WinForeground( Win *win );
XWGUI_API void WinCenter( Win *win );
XWGUI_API void WinShow( Win *win );
XWGUI_API void WinSetIcon( Win *win, const char *path );
XWGUI_API void WinSetMenu( Win *win, Menu *menu );
XWGUI_API void WinHide( Win *win );
XWGUI_API void WinClose( Win *win );
XWGUI_API const char *WinTitle( Win *win );
XWGUI_API void WinSetTitle( Win *win, const char *title );
XWGUI_API int  WinTitleWidth( Win *win, const char *title );
XWGUI_API xBool WinSizable( Win *win );
XWGUI_API void WinSetSizable( Win *win, xBool sizable );
XWGUI_API int  WinWidth( Win *win );
XWGUI_API int  WinHeight( Win *win );
XWGUI_API void WinSetWidth( Win *win, int width );
XWGUI_API void WinSetHeight( Win *win, int height );
XWGUI_API void WinSetOnClose( Win *win, WinValid valid, void *data );
XWGUI_API void WinSetOnResize( Win *win, WinAction action, void *data );
XWGUI_API xBool WinSetKey( Win *win, const char *key, WinAction action, void *data );
XWGUI_API void WinRemoveKey( Win *win, const char *key );
XWGUI_API xBool SetKey( const char *key, WinAction action, void *data );
XWGUI_API void WinFocusNext( Win *win, xBool previous );
XWGUI_API void WinSetContextMenu( Win *win, Menu *menu );
XWGUI_API void WinRemoveContextMenu( Win *win );

/* ---------------------------------------------------------------------------------------------
   Okno dialogowe: okno modalne nad oknem właściciela; kontrolki i funkcje jak w Win
   --------------------------------------------------------------------------------------------- */

XWGUI_API Win *DialogCreate( Win *owner, const char *title, int width, int height );
XWGUI_API int  DialogShowModal( Win *dialog );
XWGUI_API void DialogEnd( Win *dialog, int result );

/* ---------------------------------------------------------------------------------------------
   Panel: okno potomne na kontrolki jednej części okna; kontrolki i funkcje jak w Win
   --------------------------------------------------------------------------------------------- */

XWGUI_API Win *PanelCreate( Win *win, int x, int y, int width, int height );
XWGUI_API const char *PanelAnchor( Win *panel );
XWGUI_API void PanelSetAnchor( Win *panel, const char *anchor );

/* ---------------------------------------------------------------------------------------------
   Menu
   Skrót jak "Ctrl+S", "F1", "Alt+F4"; "" bez skrótu.
   --------------------------------------------------------------------------------------------- */

XWGUI_API xBool MenuStyle( xBool extended, int imageSize );
XWGUI_API Menu *MenuCreate( void );
XWGUI_API Menu *MenuCreatePopup( void );
XWGUI_API Menu *MenuAddMenu( Menu *menu, const char *text );
XWGUI_API Menu *MenuInsertMenu( Menu *menu, int item, const char *text );
XWGUI_API void  MenuDelete( Menu *menu, int item );
XWGUI_API void  MenuAdd( Menu *menu, const char *text, MenuAction action, void *data, const char *shortcut );
XWGUI_API void  MenuAddDisabled( Menu *menu, const char *text );
XWGUI_API void  MenuSetEnabled( Menu *menu, int item, xBool enabled );
XWGUI_API void  MenuSetRight( Menu *menu, int item );
XWGUI_API void  MenuAddSeparator( Menu *menu );

/* ---------------------------------------------------------------------------------------------
   Pasek stanu
   --------------------------------------------------------------------------------------------- */

XWGUI_API StatusBar *StatusBarCreate( Win *win, const char *text );
XWGUI_API int  StatusBarAdd( StatusBar *status, int width, const char *text, xBool raised );
XWGUI_API void StatusBarSetText( StatusBar *status, int panel, const char *text );
XWGUI_API void StatusBarSetForeground( StatusBar *status, int color );
XWGUI_API void StatusBarSetBackground( StatusBar *status, int color );
XWGUI_API void StatusBarSetScoreboard( StatusBar *status, int panel );

/* ---------------------------------------------------------------------------------------------
   Pasek przycisków; przyciski liczone od 1 bez odstępów
   --------------------------------------------------------------------------------------------- */

XWGUI_API Toolbar *ToolbarCreate( Win *win, int side );
XWGUI_API int  ToolbarAdd( Toolbar *toolbar, const char *text, ToolbarAction action, void *data );
XWGUI_API int  ToolbarAddMenu( Toolbar *toolbar, const char *text, Menu *menu );
XWGUI_API void ToolbarAddSeparator( Toolbar *toolbar );
XWGUI_API void ToolbarSetPicture( Toolbar *toolbar, int button, Picture *picture );
XWGUI_API void ToolbarSetToolTip( Toolbar *toolbar, int button, const char *text );
XWGUI_API void ToolbarSetShortcut( Toolbar *toolbar, int button, const char *shortcut );
XWGUI_API void ToolbarEnable( Toolbar *toolbar, int button, xBool enable );
XWGUI_API void ToolbarClear( Toolbar *toolbar );
XWGUI_API void ToolbarSetColor( Toolbar *toolbar, int part, int color );

/* ---------------------------------------------------------------------------------------------
   Obraz przycisku: obrazek z pliku albo znak czcionki TrueType z pliku
   --------------------------------------------------------------------------------------------- */

XWGUI_API Picture *PictureCreate( const char *file );
XWGUI_API Picture *FontIconCreate( const char *file, unsigned code, int color, int size );

/* ---------------------------------------------------------------------------------------------
   Pasek boczny
   --------------------------------------------------------------------------------------------- */

XWGUI_API Sidebar *SidebarCreate( Win *win );
XWGUI_API int  SidebarAddButton( Sidebar *sidebar, Picture *picture, const char *title, const char *shortcut );
XWGUI_API void SidebarAddAction( Sidebar *sidebar, int page, Picture *picture, const char *toolTip, SidebarAction action, void *data );
XWGUI_API void SidebarAddGlobal( Sidebar *sidebar, Picture *picture, const char *toolTip, SidebarAction action, void *data );
XWGUI_API void SidebarAddGlobalMenu( Sidebar *sidebar, Picture *picture, const char *toolTip, Menu *menu );
XWGUI_API void SidebarSetBadge( Sidebar *sidebar, int page, int count );
XWGUI_API int  SidebarPage( Sidebar *sidebar );
XWGUI_API void SidebarSetPage( Sidebar *sidebar, int page );
XWGUI_API int  SidebarWidth( Sidebar *sidebar );
XWGUI_API void SidebarSetWidth( Sidebar *sidebar, int width );
XWGUI_API void SidebarSetBarColor( Sidebar *sidebar, int color );
XWGUI_API void SidebarSetAccentColor( Sidebar *sidebar, int color );
XWGUI_API void SidebarSetBackground( Sidebar *sidebar, int color );
XWGUI_API void SidebarSetForeground( Sidebar *sidebar, int color );
XWGUI_API void SidebarSetOnChange( Sidebar *sidebar, SidebarAction action, void *data );
XWGUI_API Win *SidebarPanel( Sidebar *sidebar, int page );
XWGUI_API Win *SidebarAddSection( Sidebar *sidebar, int page, const char *title );
XWGUI_API int  SidebarAddItem( Sidebar *sidebar, int page, Picture *picture, const char *title, const char *text, const char *info, SidebarItemAction action, void *data );
XWGUI_API void SidebarSetItemSettings( Sidebar *sidebar, int page, int item, SidebarItemAction action, void *data );
XWGUI_API void SidebarSetItemEnabled( Sidebar *sidebar, int page, int item, xBool enabled );
XWGUI_API void SidebarClearItems( Sidebar *sidebar, int page );
XWGUI_API void SidebarSetMenu( Sidebar *sidebar, int page, Menu *menu );

/* ---------------------------------------------------------------------------------------------
   Komunikaty
   --------------------------------------------------------------------------------------------- */

XWGUI_API void MsgInfo( const char *text, const char *title );
XWGUI_API void MsgHelp( const char *text, const char *title );
XWGUI_API void MsgWarning( const char *text, const char *title );
XWGUI_API void MsgError( const char *text, const char *title );
XWGUI_API xBool MsgYesNo( const char *text, const char *title );
XWGUI_API xBool FileOpenDialog( const char *title, const char *filters, char *path, int size );
XWGUI_API xBool FileSaveDialog( const char *title, const char *filters, char *path, int size );

/* ---------------------------------------------------------------------------------------------
   Kontrolka: wspólne dla wszystkich kontrolek; położenie i rozmiar w pikselach logicznych (96 DPI)
   --------------------------------------------------------------------------------------------- */

XWGUI_API void ControlSetAction( Control *control, ControlAction action, void *data );
XWGUI_API void ControlSetDoubleClick( Control *control, ControlAction action, void *data );
XWGUI_API void ControlSetValid( Control *control, ControlValid valid, void *data );
XWGUI_API const char *ControlText( Control *control );
XWGUI_API void ControlSetText( Control *control, const char *text );
XWGUI_API xBool ControlVisible( Control *control );
XWGUI_API void ControlSetVisible( Control *control, xBool visible );
XWGUI_API xBool ControlEnabled( Control *control );
XWGUI_API void ControlSetEnabled( Control *control, xBool enabled );
XWGUI_API void ControlSetFocus( Control *control );
XWGUI_API xBool ControlFocused( Control *control );
XWGUI_API const char *ControlAnchor( Control *control );
XWGUI_API void ControlSetAnchor( Control *control, const char *anchor );
XWGUI_API int  ControlX( Control *control );
XWGUI_API int  ControlY( Control *control );
XWGUI_API int  ControlWidth( Control *control );
XWGUI_API int  ControlHeight( Control *control );
XWGUI_API void ControlSetX( Control *control, int x );
XWGUI_API void ControlSetY( Control *control, int y );
XWGUI_API void ControlSetWidth( Control *control, int width );
XWGUI_API void ControlSetHeight( Control *control, int height );
XWGUI_API const char *ControlToolTip( Control *control );
XWGUI_API void ControlSetToolTip( Control *control, const char *text );
XWGUI_API int  ControlColor( Control *control );
XWGUI_API void ControlSetColor( Control *control, int color );
XWGUI_API void ControlDestroy( Control *control );
XWGUI_API void ControlSetFont( Control *control, const char *name, int size, xBool bold, xBool italic );
XWGUI_API void ControlSetContextMenu( Control *control, Menu *menu );
XWGUI_API void ControlRemoveContextMenu( Control *control );

/* ---------------------------------------------------------------------------------------------
   Etykieta
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *LabelCreate( Win *win, int x, int y, int width, int height, const char *text );
XWGUI_API xBool LabelBorder( Control *label );
XWGUI_API void LabelSetBorder( Control *label, xBool border );
XWGUI_API int  LabelAlign( Control *label );
XWGUI_API void LabelSetAlign( Control *label, int align );
XWGUI_API void LabelAddLineAfter( Control *label, int color );

XWGUI_API Control *SayCreate( Win *win, int x, int y, int length, int height, const char *text );

/* ---------------------------------------------------------------------------------------------
   Pola edycji; maska (PICTURE) jak w xDev: szablon 9 # A N X L Y ! ze znakami stałymi, funkcje @! @K @R przed spacją
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *EditCreate( Win *win, int x, int y, int width, int height, const char *text );
XWGUI_API Control *MemoCreate( Win *win, int x, int y, int width, int height, const char *text );
XWGUI_API xBool EditReadOnly( Control *edit );
XWGUI_API void EditSetReadOnly( Control *edit, xBool readOnly );
XWGUI_API int  EditMaxLength( Control *edit );
XWGUI_API void EditSetMaxLength( Control *edit, int length );
XWGUI_API const char *EditPicture( Control *edit );
XWGUI_API void EditSetPicture( Control *edit, const char *picture );
XWGUI_API double EditNumber( Control *edit );
XWGUI_API void EditSetNumber( Control *edit, double number );
XWGUI_API int  EditDate( Control *edit );
XWGUI_API void EditSetDate( Control *edit, int date );

/* ---------------------------------------------------------------------------------------------
   Pola GET i ich odczyt, jak @ ... GET i ReadModal(); data jako liczba RRRRMMDD, 0 = pusta
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *GetText( Win *win, int x, int y, int length, char *value, int size, const char *picture );
XWGUI_API Control *GetMemo( Win *win, int x, int y, int length, int rows, char *value, int size );
XWGUI_API Control *GetNumber( Win *win, int x, int y, int length, double *value, const char *picture );
XWGUI_API Control *GetDate( Win *win, int x, int y, int *value );
XWGUI_API xBool WinReadModal( Win *win, Control *gets[], int count, int first );
XWGUI_API void WinEndRead( Win *win, xBool save );
XWGUI_API int  ReadLastKey( void );

/* ---------------------------------------------------------------------------------------------
   Przycisk
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *ButtonCreate( Win *win, int x, int y, int width, int height, const char *text );
XWGUI_API xBool ButtonIsDefault( Control *button );
XWGUI_API void ButtonSetDefault( Control *button, xBool isDefault );
XWGUI_API xBool ButtonIsCancel( Control *button );
XWGUI_API void ButtonSetCancel( Control *button, xBool isCancel );

/* ---------------------------------------------------------------------------------------------
   Pole wyboru i przycisk opcji
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *CheckBoxCreate( Win *win, int x, int y, int width, int height, const char *text );
XWGUI_API Control *RadioButtonCreate( Win *win, int x, int y, int width, int height, const char *text );
XWGUI_API xBool CheckBoxChecked( Control *checkBox );
XWGUI_API void CheckBoxSetChecked( Control *checkBox, xBool checked );

/* ---------------------------------------------------------------------------------------------
   Ramka
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *GroupBoxCreate( Win *win, int x, int y, int width, int height, const char *text );
XWGUI_API void GroupBoxSetLineColor( Control *groupBox, int color );

/* ---------------------------------------------------------------------------------------------
   Lista i lista rozwijana; pozycje liczone od 1
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *ListBoxCreate( Win *win, int x, int y, int width, int height );
XWGUI_API Control *ComboBoxCreate( Win *win, int x, int y, int width, int height );
XWGUI_API int  ListBoxAdd( Control *list, const char *text );
XWGUI_API void ListBoxClear( Control *list );
XWGUI_API const char *ListBoxItem( Control *list, int position );
XWGUI_API int  ListBoxCount( Control *list );
XWGUI_API int  ListBoxSelected( Control *list );
XWGUI_API void ListBoxSetSelected( Control *list, int position );
XWGUI_API const char *ListBoxSelectedText( Control *list );

/* ---------------------------------------------------------------------------------------------
   Pasek postępu
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *ProgressBarCreate( Win *win, int x, int y, int width, int height );
XWGUI_API int  ProgressBarValue( Control *progress );
XWGUI_API void ProgressBarSetValue( Control *progress, int value );
XWGUI_API int  ProgressBarMaximum( Control *progress );
XWGUI_API void ProgressBarSetMaximum( Control *progress, int maximum );

/* ---------------------------------------------------------------------------------------------
   Suwak
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *SliderCreate( Win *win, int x, int y, int width, int height );
XWGUI_API int  SliderValue( Control *slider );
XWGUI_API void SliderSetValue( Control *slider, int value );
XWGUI_API int  SliderMinimum( Control *slider );
XWGUI_API void SliderSetMinimum( Control *slider, int minimum );
XWGUI_API int  SliderMaximum( Control *slider );
XWGUI_API void SliderSetMaximum( Control *slider, int maximum );

/* ---------------------------------------------------------------------------------------------
   Pole daty
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *DatePickerCreate( Win *win, int x, int y, int width, int height );
XWGUI_API void DatePickerDate( Control *date, int *year, int *month, int *day );
XWGUI_API void DatePickerSetDate( Control *date, int year, int month, int day );

/* ---------------------------------------------------------------------------------------------
   Zakładki; strona zakładki to okno, na którym kładzie się kontrolki
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *TabControlCreate( Win *win, int x, int y, int width, int height );
XWGUI_API Win *TabControlAddPage( Control *tab, const char *title );
XWGUI_API Win *TabControlPage( Control *tab, int position );
XWGUI_API int  TabControlCount( Control *tab );
XWGUI_API int  TabControlSelected( Control *tab );
XWGUI_API void TabControlSetSelected( Control *tab, int position );

/* ---------------------------------------------------------------------------------------------
   Tabela (ListView); wiersze i kolumny liczone od 1
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *ListViewCreate( Win *win, int x, int y, int width, int height );
XWGUI_API int  ListViewAddColumn( Control *list, const char *title, int width, int align );
XWGUI_API int  ListViewAddRow( Control *list, const char *values[], int count );
XWGUI_API const char *ListViewCell( Control *list, int row, int column );
XWGUI_API void ListViewSetCell( Control *list, int row, int column, const char *text );
XWGUI_API void ListViewDelete( Control *list, int row );
XWGUI_API void ListViewClear( Control *list );
XWGUI_API int  ListViewCount( Control *list );
XWGUI_API int  ListViewColumnCount( Control *list );
XWGUI_API int  ListViewSelected( Control *list );
XWGUI_API void ListViewSetSelected( Control *list, int row );

/* ---------------------------------------------------------------------------------------------
   Drzewo (TreeView)
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *TreeViewCreate( Win *win, int x, int y, int width, int height );
XWGUI_API TreeItem *TreeViewAdd( Control *tree, const char *text );
XWGUI_API TreeItem *TreeViewAddChild( Control *tree, TreeItem *parent, const char *text );
XWGUI_API const char *TreeViewItemText( Control *tree, TreeItem *item );
XWGUI_API void TreeViewSetItemText( Control *tree, TreeItem *item, const char *text );
XWGUI_API void TreeViewExpand( Control *tree, TreeItem *item );
XWGUI_API void TreeViewCollapse( Control *tree, TreeItem *item );
XWGUI_API void TreeViewClear( Control *tree );
XWGUI_API int  TreeViewCount( Control *tree );
XWGUI_API TreeItem *TreeViewSelected( Control *tree );
XWGUI_API void TreeViewSetSelected( Control *tree, TreeItem *item );

/* ---------------------------------------------------------------------------------------------
   Tabela rekordów (Browse)
   --------------------------------------------------------------------------------------------- */

XWGUI_API Control *BrowseCreate( Win *win, int x, int y, int width, int height );
XWGUI_API void BrowseSetSource( Control *browse, BrowseMove goTop, BrowseMove goBottom, BrowseSkip skip, void *data );
XWGUI_API void BrowseSetPosition( Control *browse, BrowsePosition position );
XWGUI_API void BrowseSetEmpty( Control *browse, BrowseEmpty empty );
XWGUI_API int  BrowseAddColumn( Control *browse, const char *title, int width, int align, BrowseText text, void *data );
XWGUI_API int  BrowseAddNumber( Control *browse, const char *title, int width, const char *picture, BrowseNumber number, void *data );
XWGUI_API int  BrowseAddCheck( Control *browse, const char *title, BrowseCheck check, BrowseSetCheck setCheck, void *data );
XWGUI_API void BrowseRefresh( Control *browse );
XWGUI_API int  BrowseFreeze( Control *browse );
XWGUI_API void BrowseSetFreeze( Control *browse, int columns );
XWGUI_API int  BrowseColPos( Control *browse );
XWGUI_API void BrowseSetColPos( Control *browse, int column );
XWGUI_API int  BrowseColor( Control *browse, int part );
XWGUI_API void BrowseSetColor( Control *browse, int part, int color );

/* ---------------------------------------------------------------------------------------------
   Timer okna
   --------------------------------------------------------------------------------------------- */

XWGUI_API Timer *TimerCreate( Win *win, int interval, TimerAction action, void *data );
XWGUI_API void TimerStart( Timer *timer );
XWGUI_API void TimerStop( Timer *timer );
XWGUI_API xBool TimerActive( Timer *timer );
XWGUI_API int  TimerInterval( Timer *timer );
XWGUI_API void TimerSetInterval( Timer *timer, int interval );

/* ---------------------------------------------------------------------------------------------
   SetSys
   --------------------------------------------------------------------------------------------- */

XWGUI_API const char *Set( SetSys setting, const char *value );

/* ---------------------------------------------------------------------------------------------
   Data
   --------------------------------------------------------------------------------------------- */

XWGUI_API int DateYear( void );
XWGUI_API int Date( void );
XWGUI_API int DateAdd( int date, int days );
XWGUI_API int DateDiff( int date1, int date2 );
XWGUI_API int DOW( int date );
XWGUI_API char *Time( char *buffer, size_t size );
XWGUI_API double Seconds( void );
XWGUI_API const char *GetEnv( const char *name );

/* ---------------------------------------------------------------------------------------------
   Katalogi
   --------------------------------------------------------------------------------------------- */

/* Wpis katalogu dla DirScan(): nazwa w UTF-8, T dla katalogu i dane podane w DirScan() */
typedef void ( *DirAction )( const char *name, xBool directory, void *data );

XWGUI_API xBool DirCreate( const char *path );
XWGUI_API xBool DirExists( const char *path );
XWGUI_API char *DirTemp( char *buffer, size_t size );
XWGUI_API void  DirScan( const char *path, DirAction action, void *data );

/* ---------------------------------------------------------------------------------------------
   Pliki
   --------------------------------------------------------------------------------------------- */

XWGUI_API xBool FileExists( const char *path );
XWGUI_API xBool FileExecute( const char *file );
XWGUI_API char *MemoRead( const char *file, size_t *size );
XWGUI_API xBool MemoWrit( const char *file, const void *data, size_t size );
XWGUI_API void *LibLoad( const char *file );
XWGUI_API void *LibFunction( void *library, const char *name );
XWGUI_API xBool FileCopy( const char *source, const char *target );
XWGUI_API xBool FRename( const char *oldFile, const char *newFile );
XWGUI_API xBool FErase( const char *file );

/* ---------------------------------------------------------------------------------------------
   Tekst
   --------------------------------------------------------------------------------------------- */

/* Kompilator sprawdza argumenty formatu StringFormatSize() tak samo jak przy printf(); XWGUI_ARRAY( buffer ) to 0
   dla tablicy, a dla wskaźnika błąd kompilacji (pole bitowe o ujemnej długości), bo sizeof wskaźnika to nie rozmiar
   bufora */
#if defined( __GNUC__ ) || defined( __clang__ )
   #define XWGUI_FORMAT( formatIndex, firstArgument ) __attribute__( ( format( printf, formatIndex, firstArgument ) ) )
   #define XWGUI_ARRAY( buffer ) ( 0 * sizeof( struct { int bufor_musi_byc_tablica : 1 - 2 * __builtin_types_compatible_p( __typeof__( buffer ), __typeof__( &( buffer )[ 0 ] ) ); } ) )
#else
   #define XWGUI_FORMAT( formatIndex, firstArgument )
   #define XWGUI_ARRAY( buffer ) 0
#endif

XWGUI_API int StringFormatSize( char *buffer, size_t size, const char *format, ... ) XWGUI_FORMAT( 3, 4 );

/* StringFormat( buffer, format, ... ): StringFormatSize() z rozmiarem tablicy buffer; bufor podany wskaźnikiem idzie
   przez StringFormatSize() */
#define StringFormat( buffer, ... ) StringFormatSize( buffer, sizeof( buffer ) + XWGUI_ARRAY( buffer ), __VA_ARGS__ )
XWGUI_API char *StrTran( char *buffer, size_t size, const char *text, const char *search, const char *replace );
XWGUI_API char *RTrim( char *text );
XWGUI_API char *AllTrim( char *text );
XWGUI_API char *Upper( char *text );
XWGUI_API size_t ULen( const char *text );
XWGUI_API char *ULeft( char *text, size_t count );
XWGUI_API char *PadL( char *buffer, size_t size, const char *text, size_t length, const char *fill );
XWGUI_API char *PadC( char *buffer, size_t size, const char *text, size_t length, const char *fill );
XWGUI_API char *PadR( char *buffer, size_t size, const char *text, size_t length, const char *fill );
XWGUI_API char *DToC( int date, char *buffer, size_t size );
XWGUI_API double Round( double number, int decimals );

/* ---------------------------------------------------------------------------------------------
   Czas
   --------------------------------------------------------------------------------------------- */

XWGUI_API void IdleSleep( double seconds );

/* ---------------------------------------------------------------------------------------------
   SVG: zapis rysunku do pliku .svg
   Kolor "" w obrysie oznacza kolor pióra, promień 0 oznacza ostre narożniki.
   --------------------------------------------------------------------------------------------- */

XWGUI_API Svg *SvgInit( const char *path, int width, int height, double viewSize );
XWGUI_API void SvgClose( Svg *svg );
XWGUI_API void SvgPen( Svg *svg, double width, const char *color, xBool round );
XWGUI_API void SvgComment( Svg *svg, const char *comment );
XWGUI_API void SvgLine( Svg *svg, double x1, double y1, double x2, double y2, const char *color );
XWGUI_API void SvgFilledRect( Svg *svg, double x, double y, double width, double height, const char *color, double radius );
XWGUI_API void SvgRect( Svg *svg, double x, double y, double width, double height, double radius, const char *color );
XWGUI_API void SvgFilledCircle( Svg *svg, double cx, double cy, double r, const char *color );
XWGUI_API void SvgCircle( Svg *svg, double cx, double cy, double r, const char *color );
XWGUI_API void SvgFilledEllipse( Svg *svg, double cx, double cy, double rx, double ry, const char *color );
XWGUI_API void SvgEllipse( Svg *svg, double cx, double cy, double rx, double ry, const char *color );
XWGUI_API void SvgFilledPolygon( Svg *svg, double points[][ 2 ], int count, const char *color, double radius );
XWGUI_API void SvgPolygon( Svg *svg, double points[][ 2 ], int count, double radius, const char *color );
XWGUI_API void SvgFilledPath( Svg *svg, const char *path, const char *color );
XWGUI_API void SvgPath( Svg *svg, const char *path, const char *color );
XWGUI_API void SvgArc( Svg *svg, double cx, double cy, double r, double startAngle, double endAngle, const char *color );
XWGUI_API void SvgFilledPie( Svg *svg, double cx, double cy, double r, double startAngle, double endAngle, const char *color );
XWGUI_API void SvgPie( Svg *svg, double cx, double cy, double r, double startAngle, double endAngle, const char *color );
XWGUI_API void SvgText( Svg *svg, double x, double y, const char *text, const char *font, double size, int weight, const char *color, int align );

/* ---------------------------------------------------------------------------------------------
   WinSetState
   --------------------------------------------------------------------------------------------- */

XWGUI_API int WinSetState( Win *win, WinState state );

/* ---------------------------------------------------------------------------------------------
   Macro
   --------------------------------------------------------------------------------------------- */

#define UNUSED( n ) ( ( void )( n ) )
#define IIF( condition, trueValue, falseValue ) ( ( condition ) ? ( trueValue ) : ( falseValue ) )
#define MAX( left, right ) IIF( ( left ) > ( right ), left, right )
#define MIN( left, right ) IIF( ( left ) < ( right ), left, right )


#ifdef __cplusplus
}
#endif

#endif /* XWGUI_H */
