using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace MapEditor
{
    class pbObject
    {
        public int id;
        public PictureBox pictureBox;
        public int x;
        public int y;
        public int kind;
        public int width;
        public int height;
        public bool st; //st = static

        public pbObject()
        {
            pictureBox = new PictureBox();
            pictureBox.SizeMode = PictureBoxSizeMode.AutoSize;
        }
    }
}
