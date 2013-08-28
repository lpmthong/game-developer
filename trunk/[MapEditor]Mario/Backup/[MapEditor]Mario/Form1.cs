using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace _MapEditor_Mario
{
    public partial class Form1 : Form
    {
        private enum BlockKind
        {
            BRICK = 0,
            CLOUD = 2,
            GRASS = 3,
            FENCE = 4,
            MUSHROOM_ENEMY = 5,
            GROUND_LEFT = 7,
            GROUND_MIDDLE = 8,
            GROUND_RIGHT = 9,
            PIPE_CAP = 14,
            PIPE_BODY = 15,
            BRICK_BONUS_MUSHROOM = 16,
            TURLE = 20,
            BRICK_BONUS_GUN = 22,
            BRICK_BONUS_LIFE = 23,
            BRICK_BONUS_COIN = 24,
            OUTCOIN = 25,
            HARDBRICK = 26,
            PIRHANAPLANT = 27,
            ENDMAP = 28,
            MOUNTAIN = 29,
            HIGHTREE = 30,
            LOWTREE = 31,
            CHECKPOINT = 32,
            GROUND_SOIL = 33,
            GROUND_SOIL_LEFT = 34,
            GROUND_SOIL_RIGHT = 35,
            GROUND_DARK_SOIL = 36,
            CROSS = 37,
            BRICK_BONUS_LIFE_HIDDEN = 38,
            GROUND_MUSHROOM_RIGHT = 41,
            GROUND_MUSHROOM_MIDDLE = 42,
            GROUND_MUSHROOM_LEFT = 43,
            FALLING_CROSS = 44,
            GROUNDUNDERMUSHROOM = 45,
            BRICK_BONUS_STAR = 46,
            RED_TURLE = 39
        }

        private List<MyObj> MyList = new List<MyObj>();
        private MyObj TempObj = new MyObj();

        private bool _IsHandling;
        private bool _IsDeleting;
        private int _BlockSize = 32;

        int mapWidth = 800;

        bool bSnap = true;

        public Form1()
        {
            InitializeComponent();
            pbMap.MouseMove += new MouseEventHandler(pbMap_MouseMove);
            pbDesert.MouseMove += new MouseEventHandler(pbMap_MouseMove);
            TempObj.pb.MouseDown += new MouseEventHandler(pb_MouseDown);

            btGenerate.Click += new EventHandler(btGenerate_Click);
            btDone.Click += new EventHandler(btDone_Click);
            pbDelete.Click += new EventHandler(pbDelete_Click);
        }

        void pbDelete_Click(object sender, EventArgs e)
        {
            _IsHandling = true;
            TempObj.pb.Visible = false;
            btDone.Visible = true;
            TempObj.pb.Image = Properties.Resources.delete;
            _IsDeleting = true;
        }

        void btDone_Click(object sender, EventArgs e)
        {
            _IsHandling = false;
            TempObj.pb.Visible = false;
            btDone.Visible = false;
            if (_IsDeleting)
                _IsDeleting = false;
        }

        private void pbInList_Click(Object sender, EventArgs e)
        {
           // MessageBox.Show("Clicked at " + ((PictureBox)sender).Name);
        }

        void btGenerate_Click(object sender, EventArgs e)
        {
            SaveFileDialog save = new SaveFileDialog();
            save.Filter = "txt files (*.txt)|*.txt";
            if (save.ShowDialog() == DialogResult.OK)
            {
                FileStream fs = new FileStream(save.FileName, FileMode.Create);
                StreamWriter sw = new StreamWriter(fs);
                sw.Write(tbMapLevel1.Text);
                sw.Write(" ");
                sw.Write(tbMapLevel2.Text);
                sw.Write(" ");

                if (rdBlue.Checked)
                    sw.Write("0");
                else
                    sw.Write("1");

                foreach (MyObj obj in MyList)
                {
                    sw.Write(" ");
                    sw.Write(obj.kind);
                    sw.Write(" ");
                    sw.Write(obj.x);
                    sw.Write(" ");
                    sw.Write(obj.y);
                }

                sw.Write(" 10 0 4 0 0 300 1");

                sw.Flush();
                sw.Close();
                fs.Close();
                //save.
            }
        }

        void pb_MouseDown(object sender, MouseEventArgs e)
        {
            if (_IsDeleting)
            {
                if (MyList.Count != 0)
                {
                    int index = 1;
                    foreach (MyObj o in MyList)
                    {
                        if (o.x == TempObj.x && o.y == TempObj.y)
                        {
                            pbMap.Controls.RemoveAt(index);
                            MyList.Remove(o);
                            return;
                        }
                        else
                            index++;
                    }
                }
            }
        
            else if (_IsHandling)
            {
                int index = 1;
                foreach (MyObj o in MyList)
                {
                    if (o.x == TempObj.x && o.y == TempObj.y)
                    {
                        pbMap.Controls.RemoveAt(index);
                        MyList.Remove(o);
                        break;
                    }
                    else
                        index++;
                }
               
                MyObj temp = new MyObj();
                temp.x = TempObj.x;
                temp.y = TempObj.y;
                temp.kind = TempObj.kind;

                MyList.Add(temp);

                PictureBox pb = new PictureBox();
                pb.MouseMove += new MouseEventHandler(pbMap_MouseMove);
                pb.Image = TempObj.pb.Image;
                pb.SizeMode = PictureBoxSizeMode.AutoSize;
                pb.Location = new Point(TempObj.x, TempObj.y);
                pb.BringToFront();
                pbMap.Controls.Add(pb);
                //this.Text = "Item : " + MyList.Count;
            }
        }

        void  pbMap_MouseMove(object sender, MouseEventArgs e)
        {
            if (_IsHandling)
            {
                TempObj.pb.Visible = true;

                int x = 0;
                int y = 0;

                PictureBox pb = (PictureBox)sender;
                if (pb.Name != "pbMap")
                {
                    x = pb.Location.X;
                    y = pb.Location.Y;
                }
                if (bSnap)
                {
                    x += e.X / _BlockSize * _BlockSize;
                    y += e.Y / _BlockSize * _BlockSize;
                }
                else
                {
                    x += e.X;
                    y += e.Y;
                }
                TempObj.pb.Location = new Point(x, y);
                pbMap.Controls.Add(TempObj.pb);
                TempObj.pb.BringToFront();
                TempObj.x = x;
                TempObj.y = y;
                lbLeft.Text = x.ToString();
                lbRight.Text = y.ToString();
            }
        }

        private void pbBlock_Click(object sender, EventArgs e)
        {
            _IsDeleting = false;
            _IsHandling = true;
            TempObj.pb.Visible = false;
            btDone.Visible = true;

            string picName = ((PictureBox)sender).Name;

            if (picName == pbBlock.Name)
            {
                TempObj.pb.Image = Properties.Resources.brick;
                TempObj.kind = (int)BlockKind.BRICK;
            }
            else if (picName == pbCoin.Name)
            {
                TempObj.pb.Image = Properties.Resources.coin_empty;
                TempObj.kind = (int)BlockKind.OUTCOIN;
            }
            else if (picName == pbGrassLeft.Name)
            {
                TempObj.pb.Image = Properties.Resources.ground_left;
                TempObj.kind = (int)BlockKind.GROUND_LEFT;
            }
            else if (picName == pbGrassMid.Name)
            {
                TempObj.pb.Image = Properties.Resources.ground_middle;
                TempObj.kind = (int)BlockKind.GROUND_MIDDLE;
            }
            else if (picName == pbGrassRight.Name)
            {
                TempObj.pb.Image = Properties.Resources.ground_right;
                TempObj.kind = (int)BlockKind.GROUND_RIGHT;
            }
            else if (picName == pbDesert.Name)
            {
                TempObj.pb.Image = Properties.Resources.ground_under;
                TempObj.kind = (int)BlockKind.GROUND_SOIL;
            }
            else if (picName == pbRock.Name)
            {
                TempObj.pb.Image = Properties.Resources.rock;
                TempObj.kind = (int)BlockKind.HARDBRICK;
            }
            else if (picName == pbPipeTop.Name)
            {
                TempObj.pb.Image = Properties.Resources.pipe_cap;
                TempObj.kind = (int)BlockKind.PIPE_CAP;
            }
            else if (picName == pbPipeUnder.Name)
            {
                TempObj.pb.Image = Properties.Resources.pipe_body;
                TempObj.kind = (int)BlockKind.PIPE_BODY;
            }
            else if (picName == pbCloud.Name)
            {
                TempObj.pb.Image = Properties.Resources.cloud;
                TempObj.kind = (int)BlockKind.CLOUD;
            }
            else if (picName == pbGrass.Name)
            {
                TempObj.pb.Image = Properties.Resources.grass;
                TempObj.kind = (int)BlockKind.GRASS;
            }
            else if (picName == pbTree_Hight.Name)
            {
                TempObj.pb.Image = Properties.Resources.tree_high;
                TempObj.kind = (int)BlockKind.HIGHTREE;
            }
            else if (picName == pbTree_Low.Name)
            {
                TempObj.pb.Image = Properties.Resources.tree_low;
                TempObj.kind = (int)BlockKind.LOWTREE;
            }
            else if (picName == pbMountain.Name)
            {
                TempObj.pb.Image = Properties.Resources.mountain;
                TempObj.kind = (int)BlockKind.MOUNTAIN;
            }
            else if (picName == pbItem_Coin.Name)
            {
                TempObj.pb.Image = Properties.Resources.Item_Coin;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_COIN;
            }
            else if (picName == pbItem_Flower.Name)
            {
                TempObj.pb.Image = Properties.Resources.Item_Flower;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_GUN;
            }
            else if (picName == pbItem_RedMusrom.Name)
            {
                TempObj.pb.Image = Properties.Resources.Item_RedMusrom;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_MUSHROOM;
            }
            else if (picName == pbItem_GreenMusrom.Name)
            {
                TempObj.pb.Image = Properties.Resources.Item_GreenMusrom;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_LIFE;
            }
            else if (picName == pbDarkSoil.Name)
            {
                TempObj.pb.Image = Properties.Resources.dark_soil;
                TempObj.kind = (int)BlockKind.GROUND_DARK_SOIL;
            }
            else if (picName == pbSoilLeft.Name)
            {
                TempObj.pb.Image = Properties.Resources.soil_left;
                TempObj.kind = (int)BlockKind.GROUND_SOIL_LEFT;
            }
            else if (picName == pbSoilRight.Name)
            {
                TempObj.pb.Image = Properties.Resources.soil_right;
                TempObj.kind = (int)BlockKind.GROUND_SOIL_RIGHT;
            }
            else if (picName == pbFence.Name)
            {
                TempObj.pb.Image = Properties.Resources.fence;
                TempObj.kind = (int)BlockKind.FENCE;
            }
            else if (picName == pbMushRoomEnemy.Name)
            {
                TempObj.pb.Image = Properties.Resources.enemy_musroom;
                TempObj.kind = (int)BlockKind.MUSHROOM_ENEMY;
            }
            else if (picName == pbTurleEnemy.Name)
            {
                TempObj.pb.Image = Properties.Resources.enemy_turle;
                TempObj.kind = (int)BlockKind.TURLE;
            }
            else if (picName == pbCross.Name)
            {
                TempObj.pb.Image = Properties.Resources.cross;
                TempObj.kind = (int)BlockKind.CROSS;
            }
            else if (picName == pbHiddenLife.Name)
            {
                TempObj.pb.Image = Properties.Resources.life;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_LIFE_HIDDEN;
            }
            else if (picName == pbCheckPoint.Name)
            {
                TempObj.pb.Image = Properties.Resources.check_point;
                TempObj.kind = (int)BlockKind.CHECKPOINT;
            }
            else if (picName == pbPirhanaPlant.Name)
            {
                TempObj.pb.Image = Properties.Resources.pirhana_plant;
                TempObj.kind = (int)BlockKind.PIRHANAPLANT;
            }
            else if (picName == pbEndmap.Name)
            {
                TempObj.pb.Image = Properties.Resources.end_map;
                TempObj.kind = (int)BlockKind.ENDMAP;
            }
            else if (picName == pbMushRoomGroundRight.Name)
            {
                TempObj.pb.Image = Properties.Resources.MushRoomGroundRight;
                TempObj.kind = (int)BlockKind.GROUND_MUSHROOM_RIGHT;
            }
            else if (picName == pbMushRoomGroundLeft.Name)
            {
                TempObj.pb.Image = Properties.Resources.MushRoomGroundLeft;
                TempObj.kind = (int)BlockKind.GROUND_MUSHROOM_LEFT;
            }
            else if (picName == pbMushRoomGroundMiddle.Name)
            {
                TempObj.pb.Image = Properties.Resources.MushRoomGroundMiddle;
                TempObj.kind = (int)BlockKind.GROUND_MUSHROOM_MIDDLE;
            }
            else if (picName == pbMushRoomGroundUnder.Name)
            {
                TempObj.pb.Image = Properties.Resources.GroundUnderMushRoom;
                TempObj.kind = (int)BlockKind.GROUNDUNDERMUSHROOM;
            }
            else if (picName == pbFallingCross.Name)
            {
                TempObj.pb.Image = Properties.Resources.FallingCross;
                TempObj.kind = (int)BlockKind.FALLING_CROSS;
            }
            else if (picName == pbBonusStar.Name)
            {
                TempObj.pb.Image = Properties.Resources.BrickBonusStar;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_STAR;
            }
            else if (picName == pbRedTurle.Name)
            {
                TempObj.pb.Image = Properties.Resources.red_enemy_turle;
                TempObj.kind = (int)BlockKind.RED_TURLE;
            }
        }

        private void tbMapWidth_TextChanged(object sender, EventArgs e)
        {
            try
            {
                pbMap.Width = int.Parse(tbMapWidth.Text.ToString());
            }
            catch
            {
                MessageBox.Show("Enter a value!");
            }
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rdColor = (RadioButton)sender;

            if (rdColor.Text == "Blue")
                this.pbMap.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(100)))), ((int)(((byte)(255)))));
            else
                this.pbMap.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));

        }

        private void cbSnap_CheckedChanged(object sender, EventArgs e)
        {
            bSnap = cbSnap.Checked;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)sender;
            try
            {
                int i = int.Parse(tb.Text.ToString());
            }
            catch
            {
                MessageBox.Show("Enter a value!");
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MyList.Clear();
            _IsDeleting = _IsHandling = false;
            pbMap.Controls.Clear();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {  
            OpenFileDialog op = new OpenFileDialog();
            op.Filter = "txt files (*.txt)|*.txt";
            if (op.ShowDialog() == DialogResult.OK)
            {
                StreamReader srd = new StreamReader(op.FileName);
                String contend = srd.ReadToEnd().Trim();
                String[] spContent = contend.Split(' ');

                tbMapLevel1.Text = spContent[0];
                tbMapLevel2.Text = spContent[1];

                if (int.Parse(spContent[2]) == 0)
                {
                    rdBlue.Checked = true;
                    rdBlack.Checked = false;
                    this.pbMap.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(100)))), ((int)(((byte)(100)))), ((int)(((byte)(255)))));
                }
                else
                {
                    rdBlue.Checked = false;
                    rdBlack.Checked = true;
                    this.pbMap.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
                }

                for (int i = 3; i < spContent.Length - 7; i+=3)
                {
                    int kind = int.Parse(spContent[i]);
                    int x = int.Parse(spContent[i + 1]);
                    int y = int.Parse(spContent[i + 2]);
                    drawObject(kind, x, y);
                }
                pbMap.Width = mapWidth;
                tbMapWidth.Text = mapWidth.ToString();
            }
        }

        private void drawObject(int kind, int x, int y)
        {
            
            MyObj temp = new MyObj();
            temp.x = x;
            temp.y = y;
            temp.kind = kind;

            MyList.Add(temp);

            PictureBox pb = new PictureBox();
            pb.MouseMove += new MouseEventHandler(pbMap_MouseMove);
            //pb.Image = TempObj.pb.Image;
            pb.SizeMode = PictureBoxSizeMode.AutoSize;
            pb.Location = new Point(x, y);
            pb.BringToFront();
            
            switch (kind)
            {
                case (int)BlockKind.BRICK: pb.Image = Properties.Resources.brick; break;
                case (int)BlockKind.CLOUD: pb.Image = Properties.Resources.cloud; break;
                case (int)BlockKind.GRASS: pb.Image = Properties.Resources.grass; break;
                case (int)BlockKind.FENCE: pb.Image = Properties.Resources.fence; break;
                case (int)BlockKind.MUSHROOM_ENEMY: pb.Image = Properties.Resources.enemy_musroom; break;
                case (int)BlockKind.GROUND_LEFT: pb.Image = Properties.Resources.ground_left; break;
                case (int)BlockKind.GROUND_MIDDLE: pb.Image = Properties.Resources.ground_middle; break;
                case (int)BlockKind.GROUND_RIGHT: pb.Image = Properties.Resources.ground_right; break;
                case (int)BlockKind.PIPE_CAP: pb.Image = Properties.Resources.pipe_cap; break;
                case (int)BlockKind.PIPE_BODY: pb.Image = Properties.Resources.pipe_body; break;
                case (int)BlockKind.BRICK_BONUS_MUSHROOM: pb.Image = Properties.Resources.Item_RedMusrom; break;
                case (int)BlockKind.TURLE: pb.Image = Properties.Resources.enemy_turle; break;
                case (int)BlockKind.BRICK_BONUS_GUN: pb.Image = Properties.Resources.Item_Flower; break;
                case (int)BlockKind.BRICK_BONUS_LIFE: pb.Image = Properties.Resources.Item_GreenMusrom; break;
                case (int)BlockKind.BRICK_BONUS_COIN: pb.Image = Properties.Resources.Item_Coin; break;
                case (int)BlockKind.OUTCOIN: pb.Image = Properties.Resources.coin_empty; break;
                case (int)BlockKind.HARDBRICK: pb.Image = Properties.Resources.rock; break;
                case (int)BlockKind.PIRHANAPLANT: pb.Image = Properties.Resources.pirhana_plant; break;
                case (int)BlockKind.ENDMAP: pb.Image = Properties.Resources.end_map; break;
                case (int)BlockKind.MOUNTAIN: pb.Image = Properties.Resources.mountain; break;
                case (int)BlockKind.HIGHTREE: pb.Image = Properties.Resources.tree_high; break;
                case (int)BlockKind.LOWTREE: pb.Image = Properties.Resources.tree_low; break;
                case (int)BlockKind.CHECKPOINT: pb.Image = Properties.Resources.check_point; break;
                case (int)BlockKind.GROUND_SOIL: pb.Image = Properties.Resources.ground_under; break;
                case (int)BlockKind.GROUND_SOIL_LEFT: pb.Image = Properties.Resources.soil_left; break;
                case (int)BlockKind.GROUND_SOIL_RIGHT: pb.Image = Properties.Resources.soil_right; break;
                case (int)BlockKind.GROUND_DARK_SOIL: pb.Image = Properties.Resources.dark_soil; break;
                case (int)BlockKind.CROSS: pb.Image = Properties.Resources.cross; break;
                case (int)BlockKind.BRICK_BONUS_LIFE_HIDDEN: pb.Image = Properties.Resources.life; break;
                case (int)BlockKind.GROUND_MUSHROOM_RIGHT: pb.Image = Properties.Resources.MushRoomGroundRight; break;
                case (int)BlockKind.GROUND_MUSHROOM_LEFT: pb.Image = Properties.Resources.MushRoomGroundLeft; break;
                case (int)BlockKind.GROUND_MUSHROOM_MIDDLE: pb.Image = Properties.Resources.MushRoomGroundMiddle; break;
                case (int)BlockKind.GROUNDUNDERMUSHROOM: pb.Image = Properties.Resources.GroundUnderMushRoom; break;
                case (int)BlockKind.FALLING_CROSS: pb.Image = Properties.Resources.FallingCross; break;
                case (int)BlockKind.BRICK_BONUS_STAR: pb.Image = Properties.Resources.BrickBonusStar; break;
                case (int)BlockKind.RED_TURLE: pb.Image = Properties.Resources.red_enemy_turle; break;
            }

            pbMap.Controls.Add(pb);
            if (x > mapWidth)
                mapWidth = x + pb.Width;
        }

        private void pbMap_Click(object sender, EventArgs e)
        {

        }
    }
}
