using System;
using System.Collections.Generic;
//using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace InterProcessCommunicator
{
    public struct COPYDATASTRUCT
    {
        public IntPtr dwData;
        public int cbData;
        public IntPtr lpData;
    }

    public enum MFCMessage
    {     
        WM_WPFUI_ORDERFORM = 0x0400 + 101,
        WM_WPFUI_ORDERMANAGER = 0x0400 + 134,
        WM_WPFUI_ORDERMANAGER_R2 = 0x0400 + 136,
        WM_WPFUI_CUSTOM_CROWN_DATABASE = 0x0400 + 139,
        WM_WPFUI_SETTING = 0x0400 + 144,
    }

    public class SendMessageClass
    {

        [System.Runtime.InteropServices.DllImport("user32.dll",
        CharSet = CharSet.Auto)]
        public static extern IntPtr SendMessage(System.IntPtr hwnd, int msg,
        IntPtr wparam, IntPtr lparam);

        const int WM_COPYDATA = 0x4A;
        const int WM_CLOSE = 0x0010;

        public static void SendMessageGeneric(IntPtr handle, int msg, IntPtr wparam, IntPtr lparam)
        {
            SendMessage(handle, msg, wparam, lparam);
        }


        public static void SendMessageWithData(IntPtr destHandle, string str, IntPtr srcHandle)
        {
            COPYDATASTRUCT cds;

            cds.dwData = srcHandle;
            str = str + '\0'; 

            //cds.cbData  = str.Length + 1;
            cds.cbData = System.Text.Encoding.Default.GetBytes(str).Length + 1;
            cds.lpData  = Marshal.AllocCoTaskMem(str.Length);
            cds.lpData  = Marshal.StringToCoTaskMemAnsi(str);
            IntPtr iPtr = Marshal.AllocCoTaskMem(Marshal.SizeOf( cds));
            Marshal.StructureToPtr(cds,iPtr, true);

            // send to the MFC app
            SendMessage(destHandle, WM_COPYDATA, IntPtr.Zero, iPtr);

            // Don't forget to free the allocatted memory 
            Marshal.FreeCoTaskMem(cds.lpData);
            Marshal.FreeCoTaskMem(iPtr);
        }

        public static void SendMessageWithDataUsingHGlobal(IntPtr destHandle, string str, IntPtr srcHandle)
        {
            COPYDATASTRUCT cds;

            cds.dwData = srcHandle;
            str = str + '\0';

            cds.cbData = str.Length + 1;
            cds.lpData = Marshal.AllocHGlobal(str.Length);
            cds.lpData = Marshal.StringToHGlobalAnsi(str);
            IntPtr iPtr = Marshal.AllocHGlobal(Marshal.SizeOf(cds));
            Marshal.StructureToPtr(cds, iPtr, true);

            // send to the MFC app
            SendMessage(destHandle, WM_COPYDATA, srcHandle, iPtr);

            // Don't forget to free the allocatted memory 
            Marshal.FreeCoTaskMem(cds.lpData);
            Marshal.FreeCoTaskMem(iPtr);
        }
    }
}