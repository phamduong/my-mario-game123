using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace MapEditor
{
    enum CursorMode
    {
        normal,     //do nothing
        draw,       //drawing mode
        move,       //move object
        drag,       //drag the whole map
        zoomin,     //zoom in map
        zoomout     //zoom out map
    }

    public partial class FormMain : Form
    {
        int mWidth;          //Map width
        int mHeight;         //Map height
        ArrayList picBoxGroup = new ArrayList();    //List of all picture box controls
        PictureBox picSelected;                    //Current selected picture box
        //Bitmap drawArea;                            //..
        Graphics mGraphic;
        Cursor curCursor;                           //Current cursor
        public static bool isInside = true;                //Is cursor inside map area
        string folder;                              //Store project folder path
        int oldX, oldY;                                   //Map when mouse drag
        CursorMode currMode;                        //Current cursor mode
        public static GameObject objectSelected;           //Selected game object
        Cursor dragCursor;
        Cursor handCursor;
        Cursor zoominCursor;
        Cursor zoomoutCursor;

        //Draw line around game object
        Graphics graphic;
        Pen pen;

        public FormMain()
        {
            InitializeComponent();
            this.KeyUp += FormMain_KeyUp;
            this.KeyDown += FormMain_KeyDown;
            this.Paint += FormMain_Paint;
            LoadComponent();
        }


        /// <summary>
        /// Load ...
        /// </summary>
        private void LoadComponent()
        {
            //Get project folder's path
            folder = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.FullName;

            //Load all cursors' icon
            dragCursor = CustomCursor.CreateCursorFromFile(folder, "cursor_drag_arrow.png", 18, 18);
            handCursor = CustomCursor.CreateCursorFromFile(folder, "cursor_drag_hand.png", 18, 18);
            zoominCursor = CustomCursor.CreateCursorFromFile(folder, "cursor_zoom_in.png", 18, 18);
            zoomoutCursor = CustomCursor.CreateCursorFromFile(folder, "cursor_zoom_out.png", 18, 18);

            //graphic = this.CreateGraphics();
            pen = new Pen(Color.Red);
            pen.Width = 10;

            //Get all tab pages
            IEnumerator wrapEnum = tabControl.Controls.GetEnumerator();
            wrapEnum.Reset();
            while (wrapEnum.MoveNext())
            {
                TabPage tp = (TabPage)wrapEnum.Current;
                //Ignore properties tab
                if (tp.Name != "tabProperties")
                {
                    //In 1 tab page get all picture box control
                    IEnumerator tabEnum = tp.Controls.GetEnumerator();
                    tabEnum.Reset();
                    while (tabEnum.MoveNext())
                    {
                        //Add to list picture box controls
                        picBoxGroup.Add((PictureBox)tabEnum.Current);
                    }
                }

            }

            //Set picture box control properties and add event handler when click on a picture box
            foreach (PictureBox p in picBoxGroup)
            {
                p.BorderStyle = BorderStyle.FixedSingle;
                p.Click += p_Click;
            }

            //Load draw area for class graphic ???????
            //drawArea = new Bitmap(picbMap.Size.Width, picbMap.Size.Height);
            //picbMap.Image = drawArea;
            //mGraphic = Graphics.FromImage(drawArea);
        }

        void FormMain_KeyDown(object sender, KeyEventArgs e)
        {
            //if (e.KeyCode == Keys.Delete)
            //{
            //    int t = 1;
            //    picbMap.Controls.Remove(FormMain.objectSelected);
            //    FormMain.objectSelected = null;
            //}
            //MessageBox.Show(isInside.ToString());
            if (isInside == true)
            {
                //If control key is hold and cursor is inside map area -> change to move cursor
                if (e.KeyCode == Keys.ControlKey)
                {
                    //Change to move cursor
                    if (this.Cursor != dragCursor)
                    {
                        this.Cursor = dragCursor;
                        currMode = CursorMode.move;
                    }
                }
                //If space key is pressed -> change to hand cursor
                else if (e.KeyCode == Keys.Space)
                {
                    if (this.Cursor != handCursor)
                    {
                        this.Cursor = handCursor;
                        currMode = CursorMode.drag;
                    }
                }
                //If ALT key is pressed -> change to zoom in cursor                    
                else if (e.KeyCode == Keys.Z)
                {
                    if (this.Cursor != zoominCursor)
                    {
                        this.Cursor = zoominCursor;
                        currMode = CursorMode.zoomin;
                    }
                }
                //If ALT + SHIFT is pressed -> change to zoom out cursor
                else if(e.KeyCode == Keys.X)
                {
                    if (this.Cursor != zoominCursor)
                    {
                        this.Cursor = zoomoutCursor;
                        currMode = CursorMode.zoomout;
                    }
                    
                }
                //If delete game object
                else if (e.KeyCode == Keys.Delete)
                {
                    picbMap.Controls.Remove(FormMain.objectSelected);
                    FormMain.objectSelected = null;
                }
                //If user press escape
                else if (e.KeyCode == Keys.Escape)
                {
                    this.Cursor = Cursors.Default;
                    picSelected = null;
                    FormMain.objectSelected.BorderStyle = BorderStyle.None;
                    FormMain.objectSelected.isSelected = false;
                    FormMain.objectSelected = null;
                }
            }
        }

        void FormMain_KeyUp(object sender, KeyEventArgs e)
        {
            //If Escape key
            if (e.KeyCode == Keys.Escape)
            {
                currMode = CursorMode.normal;
            }
            else
            {
                //Return to current cursor
                this.Cursor = curCursor;
                currMode = CursorMode.draw;
            }
            
        }


        

        /// <summary>
        /// Picture box controls' click event handler
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void p_Click(object sender, EventArgs e)
        {
            if (picSelected != null)
            {
                //Make sure that only 1 picture has select effect at one time
                picSelected.BorderStyle = BorderStyle.FixedSingle;
            }
           
            //--
            picSelected = (PictureBox)sender;
            picSelected.BorderStyle = BorderStyle.Fixed3D;
            currMode = CursorMode.draw;
        }

        /// <summary>
        /// Apply map's properties
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btApply_Click(object sender, EventArgs e)
        {
            try
            {
                mWidth = Int32.Parse(txtWidth.Text);
                mHeight = Int32.Parse(txtHeight.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Check input value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtWidth.Clear();
                txtHeight.Clear();
                txtWidth.Focus();
                return;
            }

            if (mWidth < 500 || mHeight < 300)
            {
                //Check input value
                MessageBox.Show("Map is too small. Input bigger value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtWidth.Focus();
            }
            else
            {
                //Set width and height for map
                picbMap.Width = mWidth;
                picbMap.Height = mHeight;
            }
        }


        /// <summary>
        /// Draw on map
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void picbMap_MouseClick(object sender, MouseEventArgs e)
        {
            //If in normal-draw mode
            if (picSelected != null && currMode == CursorMode.draw && e.Button == MouseButtons.Left)
            {
                //Deselect current game selected object
                if (FormMain.objectSelected != null)
                {
                    FormMain.objectSelected.BorderStyle = BorderStyle.None;
                    FormMain.objectSelected.isSelected = false;
                    FormMain.objectSelected = null;
                }
                //mGraphic.DrawImage(picSelected.Image, e.X, e.Y, (float)picSelected.Image.Size.Width, (float)picSelected.Image.Size.Height);
                //picbMap.Image = drawArea;
                //mGraphic.Dispose();
                //PictureBox temp = new PictureBox();
                //temp.Image = picSelected.Image;
                //temp.SizeMode = PictureBoxSizeMode.CenterImage;
                //temp.Height = picSelected.Image.Height;
                //temp.Width = picSelected.Image.Width;
                //temp.Left = e.X;
                //temp.Top = e.Y;
                GameObject temp = new GameObject(picSelected.Image, e.X, e.Y);
                FormMain.objectSelected = temp;
                
                picbMap.Controls.Add(temp);
                //Cursor is inside map's area
                FormMain.isInside = true;
            }
        }

        /// <summary>
        /// Change mouse image when enter map's area
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void picbMap_MouseEnter(object sender, EventArgs e)
        {
            //Cursor is inside map area
            isInside = true;
            if (picSelected != null && currMode == CursorMode.draw)
            {
                //Change cursor to current selected object's image
                Bitmap bitmap = new Bitmap(picSelected.Image);
                curCursor = CustomCursor.CreateCursor(bitmap, 1, 1);
                this.Cursor = curCursor;
                bitmap.Dispose();
                
            }
        }

        /// <summary>
        /// Reset mouse to default when leave map's area
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void picbMap_MouseLeave(object sender, EventArgs e)
        {
            if (!panelMain.ClientRectangle.Contains(PointToClient(Control.MousePosition)))
            {
                //Cursor move outside map area
                isInside = false;
            }
            //Change cursor to default
            //curCursor = Cursors.Default;
            this.Cursor = Cursors.Default;
            currMode = CursorMode.draw;
        }

        private void picbMap_MouseDown(object sender, MouseEventArgs e)
        {
            //If user want to drag this map 
            if (currMode == CursorMode.drag)
            {
                oldX = e.X;
                oldY = e.Y;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void picbMap_MouseMove(object sender, MouseEventArgs e)
        {
            //If user drag the whole map
            if (currMode == CursorMode.drag && e.Button == MouseButtons.Left)
            {
                int movex = e.X - oldX;
                int movey = e.Y - oldY;
                //Bound in panel main
                if (movex > 0)
                {
                    if(picbMap.Left < panelMain.Left){
                        picbMap.Left += movex;
                    }
                }else if(movex < 0){
                    if (picbMap.Right > panelMain.Right)
                    {
                        picbMap.Left += movex;
                    }
                    
                }

                if (movey > 0)
                {
                    if (picbMap.Top < panelMain.Top)
                    {
                        picbMap.Top += movey;
                    }
                }
                else if (movex < 0)
                {
                    if (picbMap.Bottom > panelMain.Bottom)
                    {
                        picbMap.Top += movey;
                    }
                }
            }else if (currMode == CursorMode.move && e.Button == MouseButtons.Left)
            {
                //If user move game object
                int movex = e.X - FormMain.objectSelected.Location.X - FormMain.objectSelected.Image.Width /2;
                int movey = e.Y - FormMain.objectSelected.Location.Y - FormMain.objectSelected.Image.Height /2;
                FormMain.objectSelected.Left += movex;
                FormMain.objectSelected.Top += movey;
                this.Invalidate();
            }
        }

       protected override void OnPaint(PaintEventArgs e)
        {
 	         base.OnPaint(e);
            
        }


       void FormMain_Paint(object sender, PaintEventArgs e)
       {
           graphic = e.Graphics;
           graphic.DrawLine(pen, 50, 50, 400, 300);
           foreach (GameObject o in picbMap.Controls)
           {
               if (o != FormMain.objectSelected)
               {
                  
                   //o.BorderStyle = BorderStyle.Fixed3D;
                   //graphic.DrawLine(pen, o.Location.X - 10, o.Location.Y - 10,
                   //       o.Location.X + o.Size.Width + 10, o.Location.Y + o.Height + 10);
                  
               }
           }
       }

        private void panelMain_MouseMove(object sender, MouseEventArgs e)
        {
        }
    }
}
