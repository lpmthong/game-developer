using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;
using System.Drawing;

namespace MapEditor
{
    class QuadTree
    {
        public QuadNode root;
        public int map_width;
        public int map_height;
        public int Min_Node_Width = 450;

        public QuadTree(int mapwidth, int mapheight, List<CTreeObject> listTreeObj)
        {
            map_width = mapwidth;
            map_height = mapheight;
            root = new QuadNode(0, 0, map_width, map_height, "");
            root.listTreeObj = listTreeObj;
        }

        public void Build()
        {
            Build(root);
        }

        public void Build(QuadNode iroot)
        {
            int node_width = (iroot.rect.Right - iroot.rect.Left) / 2;            
            if (node_width < Min_Node_Width)
                return;

            iroot.LT = new QuadNode(iroot.rect.Left, iroot.rect.Top, node_width, node_width, iroot.id + "00");            
            iroot.LB = new QuadNode(iroot.rect.Left, iroot.rect.Top + node_width, node_width, node_width, iroot.id + "01");
            iroot.RT = new QuadNode(iroot.rect.Left + node_width, iroot.rect.Top, node_width, node_width, iroot.id + "10");            
            iroot.RB = new QuadNode(iroot.rect.Left + node_width, iroot.rect.Top + node_width, node_width, node_width, iroot.id + "11");
            
            foreach (CTreeObject obj in iroot.listTreeObj)
            {
                Clip(obj, iroot.LT);
                Clip(obj, iroot.LB);
                Clip(obj, iroot.RT);
                Clip(obj, iroot.RB);
            }

            iroot.listTreeObj = null;

            if (iroot.LT.listTreeObj.Count > 0)
                Build(iroot.LT);
            if (iroot.LB.listTreeObj.Count > 0)
                Build(iroot.LB);
            if (iroot.RT.listTreeObj.Count > 0)
                Build(iroot.RT);
            if (iroot.RB.listTreeObj.Count > 0)
                Build(iroot.RB);
        }

        public void Clip(CTreeObject o, QuadNode iroot)
        {
            if (CheckPointInRect(o.left, o.top, iroot.rect) && CheckPointInRect(o.right, o.bottom, iroot.rect))
            {                
                iroot.listTreeObj.Add(o);               
                return;
            }

            Rectangle RectCtreeObj = new Rectangle(o.left, o.top, o.right - o.left, o.bottom - o.top);
            Rectangle result = new Rectangle();
            result = Rectangle.Intersect(iroot.rect, RectCtreeObj);
            if (!result.IsEmpty)
            {
                CTreeObject temp = new CTreeObject();
                temp.target = o.target;
                temp.left = result.Left;
                temp.top = result.Top;
                temp.bottom = result.Bottom;
                temp.right = result.Right;

                iroot.listTreeObj.Add(temp);
            }            
        }

        public bool CheckPointInRect(int x, int y, Rectangle rect)
        {
            if (x >= rect.Left && x <= rect.Right && y >= rect.Top && y <= rect.Bottom)
                return true;            
            return false;
        }

        public void Save(string filename)
        {
            int length = filename.Length;
            int start = length - 4;
            filename = filename.Insert(start, "QuadTree");

            FileStream fs = new FileStream(filename, FileMode.Create);
            StreamWriter sw = new StreamWriter(fs);

            SaveNode(root, sw);

            sw.Flush();
            sw.Close();
            fs.Close();
        }

        public void SaveNode(QuadNode iroot, StreamWriter sw)
        {
            string str = iroot.Serialize();
            if (!str.Equals(""))
                sw.WriteLine(str);
            if (iroot.LT != null) 
                SaveNode(iroot.LT, sw);            
            if (iroot.LB != null)
                SaveNode(iroot.LB, sw);
            if (iroot.RT != null)
                SaveNode(iroot.RT, sw);
            if (iroot.RB != null)
                SaveNode(iroot.RB, sw);
        }
        
    }
}
