#include "ofxPrint.h"
#include <Commdlg.h>
#include <WinSpool.h>
#include <OCIdl.h>
#include <OleCtl.h>
IPicture* LoadPicture(LPCSTR szFile)   
{   
    // open file    
    HANDLE hFile = CreateFileA(szFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);   
	
    if (INVALID_HANDLE_VALUE == hFile)   
    {   
        return NULL;   
    }   
    else   
    {   
        // get file size    
        int nFileSize = GetFileSize(hFile, NULL);   
		
        IPicture * pPicture = NULL;   
		
        if (nFileSize > 0)   
        {   
            // alloc memory based on file size    
            HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nFileSize);   
			
            LPVOID pvData = GlobalLock(hGlobal);   
			
            DWORD dwBytesRead = 0;   
            // read file and store in global memory    
            BOOL bRead = ReadFile(hFile, pvData, nFileSize, &dwBytesRead, NULL);   
			
            GlobalUnlock(hGlobal);   
			
            LPSTREAM pstm = NULL;   
			
            HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);   
			
            //assert(SUCCEEDED(hr) && pstm);   
			
            hr = ::OleLoadPicture(pstm, nFileSize, FALSE, IID_IPicture, (LPVOID *)&pPicture);   
            //assert(SUCCEEDED(hr) && pPicture);     
			
            pstm->Release();   
			
        }   
		
        CloseHandle(hFile);   
		
        return pPicture;   
    }   
} 

void PrintPicture(LPCSTR pFileName)   
{   
    IPicture * pPicture = LoadPicture(pFileName);  	
    if (pPicture)   
    {   
        PRINTDLG pd;   		
        memset(&pd, 0, sizeof(pd));   		
        pd.lStructSize = sizeof(PRINTDLG);   
        pd.Flags = PD_RETURNDC | PD_RETURNDEFAULT;   		
        if (PrintDlg(&pd))   
        {   
            HDC hdc = pd.hDC;
			
            DOCINFOA docinfo;   			
            memset(&docinfo, 0, sizeof(docinfo));   			
            docinfo.cbSize = sizeof(docinfo);   
            docinfo.lpszDocName = pFileName;   			
            StartDocA(hdc, &docinfo);   
            StartPage(hdc);   		
            {   
                long bmWidth;   
                long bmHeight;   				
                pPicture->get_Width(&bmWidth);   
                pPicture->get_Height(&bmHeight);   				
                // convert himetric to pixels   
                int nWidth  = GetDeviceCaps(hdc, HORZRES);   
                int nHeight = GetDeviceCaps(hdc, VERTRES);   
                int dx      = 0;   
                int dy      = 0;  				
                // margin    
                {   
                    int nLeft   = GetDeviceCaps(hdc, PHYSICALOFFSETX);   
                    int nTop    = GetDeviceCaps(hdc, PHYSICALOFFSETY);  					
                    int nRight  = GetDeviceCaps(hdc, PHYSICALWIDTH)  - nLeft - nWidth;   
                    int nBottom = GetDeviceCaps(hdc, PHYSICALHEIGHT) - nTop  - nHeight;   					
                    int nLR     = max(nLeft, nRight);   
                    int nBT     = max(nTop, nBottom);   					
                    dx = nLR - nLeft;   
                    dy = nBT - nTop;   					
                    nWidth  = GetDeviceCaps(hdc, PHYSICALWIDTH)   - nLR * 2;   
                    nHeight = GetDeviceCaps(hdc, PHYSICALHEIGHT)  - nBT * 2;   
                }   				
                float scalex = (float) nWidth  / bmWidth;   
                float scaley = (float) nHeight / bmHeight;   
                //float scale  = min(scalex, scaley);   				
                int w = (int) (bmWidth  * scalex);   
                int h = (int) (bmHeight * scaley);   				
                dx += (nWidth  - w) / 2;   
                dy += (nHeight - h) / 2;   				
                pPicture->Render(hdc, dx, dy, w, h, 0, bmHeight, bmWidth, -bmHeight, NULL);   
            }   			
            EndPage(hdc);   
            EndDoc(hdc);   			
            DeleteDC(hdc);   		
		}		
        pPicture->Release();   
    }   
}   