#include "NxVideoPreCompiled.h"

namespace NxVideo_Namespace {

struct NxVideoDeviceVFW
{
public:
	BYTE * Buffer;
	HWND m_hWnd ;
	NxVideoDeviceVFW() : Buffer( 0 )
	{

	}

	~NxVideoDeviceVFW()
	{

	}

} ;
 
NxVideoGrabberVFW::NxVideoGrabberVFW() : NxVideo_Grabber()
{
	mVideo = new NxVideoDeviceVFW();
	mType = NxVideoCaptureVFW ;
}
 
NxVideoGrabberVFW::~NxVideoGrabberVFW()
{
	 
}

bool VFW_GetCAPDRIVERCAPS( HWND m_hWnd )
{
	CAPDRIVERCAPS  m_CAPDRIVERCAPS ;
    bool ok = 0!=capDriverGetCaps( m_hWnd , &m_CAPDRIVERCAPS, sizeof(CAPDRIVERCAPS));
    if (ok)
    {
		bool m_has_overlay = 0!= m_CAPDRIVERCAPS.fHasOverlay ;
    }
    else{}
    return ok;
}

bool GetVideoFormat( HWND m_hWnd, int *width, int *height, int *bpp, FOURCC *fourcc)
{
    int bmpformatsize = capGetVideoFormatSize( m_hWnd );
    if (bmpformatsize)
    {
        BITMAPINFO *lpbmpinfo = (BITMAPINFO*)(new char[bmpformatsize]);
        bmpformatsize = capGetVideoFormat(m_hWnd , lpbmpinfo, (WORD)bmpformatsize);
        if (width)  *width = lpbmpinfo->bmiHeader.biWidth;
        if (height) *height = lpbmpinfo->bmiHeader.biHeight;
        if (bpp)    *bpp = lpbmpinfo->bmiHeader.biBitCount;
        if (fourcc) *fourcc = lpbmpinfo->bmiHeader.biCompression;
        delete []lpbmpinfo;
        return true;
    }
    
	/*
    if (width)  *width = 0;
    if (height) *height = 0;
    if (bpp)    *bpp = 0;
    if (fourcc) *fourcc = wxNullFOURCC;
	*/
    return false;
}

void videoFrame( LPVIDEOHDR lpVHdr, NxVideoGrabberVFW * pointer  )
{
	int count = lpVHdr->dwBytesUsed;
	const int dataSize = pointer->GetWidth() * pointer->GetHeight() * pointer->GetBpp() ;
	if(count < dataSize)
	{ 
		//Ogre::LogManager::getSingleton().logMessage("NxVideo: videoFrame( LPVIDEOHDR lpVHdr ), not enough pixels to complete frame");
		return;
	}

	//memcpy( &PixelBuffer[0] , &lpVHdr->lpData[0] , dataSize  );
	pointer->mVideoData = lpVHdr->lpData ;
	pointer->mNewFrame = true ;
	return ;
}

static LRESULT CALLBACK fcb( HWND hWnd, LPVIDEOHDR lpVHdr )
{
	NxVideoGrabberVFW * pointer  = ( NxVideoGrabberVFW * )( capGetUserData(hWnd) );
	if( pointer )
	{
		if( lpVHdr->dwBufferLength > 0)
		{
			videoFrame(lpVHdr, pointer );
			return (LRESULT) true ;
		}
	}
	return (LRESULT) false ;
}

bool NxVideoGrabberVFW::OpenVideoDevice( unsigned long Index , int Width , int Height, int BPP )
{
    mVideo->m_hWnd = capCreateCaptureWindow((LPSTR)"Capture Window",WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS,0, 0,Width ,Height ,(HWND)GetDesktopWindow(), 120  ); // capwindow ID?
	ShowWindow( mVideo->m_hWnd, SW_HIDE );
 
	mVideoWidth = Width;
	mVideoHeight = Height ;
	mVideoBpp = BPP;
	mDeviceIndex = Index ;
	mVideoData = (BYTE *) new BYTE[ Width * Height * BPP ]; 
	bool m_deviceIndex = (0!=capDriverConnect( mVideo->m_hWnd , Index ))? Index : -1;

	CAPTUREPARMS params;
	if (!capCaptureGetSetup( mVideo->m_hWnd , &params, sizeof(CAPTUREPARMS))){ return false; }

	params.fYield = TRUE;
	params.fCaptureAudio = FALSE;
	params.wPercentDropForError = 100;
	params.fLimitEnabled = FALSE;
	params.AVStreamMaster = AVSTREAMMASTER_NONE;
	params.fStepCaptureAt2x = FALSE;
	params.fAbortLeftMouse = FALSE;
	params.fAbortRightMouse = FALSE;

	if(!capCaptureSetSetup( mVideo->m_hWnd , &params, sizeof(CAPTUREPARMS))){ return false ; }

	if (!capSetCallbackOnVideoStream( mVideo->m_hWnd , fcb ))
	{
		Log("Could not set capSetCallbackOnVideoStream.");
		return false ;
	}

	if(!capSetUserData( mVideo->m_hWnd, this))
    {
		Log("Could bnot set user data");
		return false ;
    }
	DWORD formSize = capGetVideoFormat( mVideo->m_hWnd, NULL, 0);
	BITMAPINFO *videoFormat = (BITMAPINFO *)(new char[formSize]);
	if (!capGetVideoFormat( mVideo->m_hWnd, videoFormat, formSize))
    {
		Log("Could not capGetVideoFormat");
		return false ;
    }
	videoFormat->bmiHeader.biWidth = mVideoWidth;
	videoFormat->bmiHeader.biHeight = mVideoHeight;
	videoFormat->bmiHeader.biBitCount = 24;
	videoFormat->bmiHeader.biCompression = BI_RGB;
	videoFormat->bmiHeader.biClrUsed = 0;
	videoFormat->bmiHeader.biClrImportant = 0;
	videoFormat->bmiHeader.biSizeImage = 0;
	if (!capSetVideoFormat( mVideo->m_hWnd, videoFormat, formSize))
    {
		Log("Could not capSetVideoFormat");
		return false ;
    }

	delete videoFormat;
	capCaptureSequenceNoFile( mVideo->m_hWnd );
	return true;
}

bool NxVideoGrabberVFW::CloseVideoDevice()
{
	if( mVideo->m_hWnd )
	{ 
		capCaptureSequenceNoFile( NULL );
		capCaptureStop( mVideo->m_hWnd );
		capDriverConnect( mVideo->m_hWnd , mDeviceIndex );
		if(!capDriverDisconnect( mVideo->m_hWnd ))Log("Cant disconnect driver");
		capCaptureAbort( mVideo->m_hWnd );
		capSetCallbackOnVideoStream( mVideo->m_hWnd, NULL);
		DestroyWindow( mVideo->m_hWnd);
		mVideo->m_hWnd = NULL ;
		return true ;
	}

	return false ;
}

unsigned char * NxVideoGrabberVFW::GetBuffer()
{
	if( mNewFrame )
	{
		mNewFrame = false ;
		return mVideoData;
	}
	return 0;
}

bool NxVideoGrabberVFW::NewFrame()
{
	return mNewFrame;
}

 

}//namespace