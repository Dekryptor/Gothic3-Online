#ifndef _ECWND_H
#define _ECWND_H
enum eEWinTextMode
{
	winUnk1,
	winUnk2,
	winUnk3
};
class DLLIMPORT eCWnd
{
public:
	eCWnd( const eCWnd & );
	eCWnd( void );
protected: virtual ~eCWnd( void );
public:
	static eCWnd* STDCALL GetDesktopWindow( void );
	virtual void SetTitleBarText( const bCString & );
	virtual bCString GetTitleBarText( void ) const;
	void ClearPrintWin( void );
	void Print( const bCPoint &, const bCString &, const bCByteAlphaColor *, eEWinTextMode);
	bCPoint GetDesktopPosition( void ) const;
};
#endif