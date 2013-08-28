using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace _MapEditor_Mario
{
    public class MyObj
    {
        public PictureBox pb;
        public int x;
        public int y;
        public int kind;

        public MyObj()
        {
            pb = new PictureBox();
            pb.SizeMode = PictureBoxSizeMode.AutoSize;
        }            
    }
}
