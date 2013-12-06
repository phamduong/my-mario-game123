using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace MapEditor
{
    public class GameObject: PictureBox
    {
        public bool isSelected;                        //Does object is selected by user or not
        public GameObject(Image image, int x, int y)
        {
            this.Image = image;
            this.SizeMode = PictureBoxSizeMode.CenterImage;
            this.Height = image.Height;
            this.Width = image.Width;
            this.Left = x;
            this.Top = y;
            this.MouseDown += ProcessLeftMouseClick;
            this.MouseEnter += ProcessMouseEnter;
            this.isSelected = true;
            this.BorderStyle = BorderStyle.Fixed3D;

            //Deselect
            if (FormMain.objectSelected != null)
            {
                FormMain.objectSelected.BorderStyle = BorderStyle.None;
                FormMain.objectSelected.isSelected = false;
            }
        }

        //When click on a game object
        private void ProcessLeftMouseClick(object sender, MouseEventArgs e)
        {
            //Cursor is inside map's area
            FormMain.isInside = true;
            if (FormMain.objectSelected != null)
            {
                FormMain.objectSelected.BorderStyle = BorderStyle.None;
                FormMain.objectSelected.isSelected = false;
            }
            this.BorderStyle = BorderStyle.Fixed3D;
            this.isSelected = true;
            FormMain.objectSelected = (GameObject)sender;
        }

        private void ProcessMouseEnter(object sender, EventArgs e)
        {
            //Cursor is inside map's area
            FormMain.isInside = true;
        }
    }
}
