using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace MapEditor
{
    class QuadNode
    {
        public string id;
        public List<CTreeObject> listTreeObj = new List<CTreeObject>();
        public QuadNode LT, RT, LB, RB;
        public Rectangle rect;
        

        public QuadNode(int left, int top, int width, int height, string _id)
        {
            id = _id;
            rect = new Rectangle(left, top, width, height);
            LT = RT = LB = RB = null;            
        }

        public string Serialize()
        {
            if (id.Equals(""))
                return "";
            string str = id + " " + rect.Left.ToString() + " " + rect.Top.ToString() + " "
                            + rect.Right.ToString() + " " + rect.Bottom.ToString() + " ";            
            if (listTreeObj != null)
            {
                int i = listTreeObj.Count;
                if (i == 0)
                {
                    str += "0";
                    return str;
                }
                foreach (CTreeObject obj in listTreeObj)
                {
                    str += obj.target.id;
                    if (i > 1)
                    str += " ";
                    i--;
                }
            }
            else
            {
                str += "0";
            }         
            
            return str;
        }
    }
}
