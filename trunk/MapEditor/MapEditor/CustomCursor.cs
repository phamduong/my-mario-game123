using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace MapEditor
{
    //Mimic ICONINFO structure 
    //http://msdn.microsoft.com/en-us/library/ms648052(VS.85).aspx
    public struct IconInfo
    {
        public bool fIcon;              //Whether this struct defines an icon or cursor
        public int xHotSpot;
        public int yHotSpot;
        private IntPtr hbmMask;          //
        private IntPtr hbmColor;
    }
    public class CustomCursor
    {
        [DllImport("user32.dll")]
        private static extern IntPtr CreateIconIndirect(ref IconInfo icon);

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetIconInfo(IntPtr hIcon, ref IconInfo pIconInfo);

        public static Cursor CreateCursor(Bitmap bmp, int xHotSpot, int yHotSpot)
        {
            IconInfo tmp = new IconInfo();
            GetIconInfo(bmp.GetHicon(), ref tmp);
            tmp.xHotSpot = xHotSpot;
            tmp.yHotSpot = yHotSpot;
            tmp.fIcon = false;          //This property will make cursor
            return new Cursor(CreateIconIndirect(ref tmp));
        }


        public static Cursor CreateCursorFromFile(string folder, string filename, int cursorWidth, int cursorHeight)
        {
            Image image = null;
            try
            {
                image = Image.FromFile(folder + "\\Images\\Cursor\\" + filename);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("Hum. Maybe some thing error, i will fix it later!");
            }

            Bitmap bitmap = new Bitmap(cursorWidth, cursorHeight);
            Graphics g = Graphics.FromImage((Image)bitmap);
            g.InterpolationMode = InterpolationMode.HighQualityBicubic;
            g.DrawImage(image, 0, 0, cursorWidth, cursorHeight);
            g.Dispose();
            int spotX = bitmap.Width / 2;
            int spotY = bitmap.Height / 2;
            Cursor c = CustomCursor.CreateCursor(bitmap, spotX, spotY);
            return c;
        }
    }
}
