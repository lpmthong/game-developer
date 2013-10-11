using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace MapEditor
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }

        #region Properties

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
            RED_TURLE = 39,
            GROUND_MUSHROOM_RIGHT = 41,
            GROUND_MUSHROOM_MIDDLE = 42,
            GROUND_MUSHROOM_LEFT = 43,
            FALLING_CROSS = 44,
            GROUNDUNDERMUSHROOM = 45,
            BRICK_BONUS_STAR = 46            
        }

        private pbObject TempObj = new pbObject();
        private List<pbObject> listPbObject= new List<pbObject>();
        private bool _IsDeleting = false;
        private bool _IsHandling = false;
        private int BlockSize = 32;
        private int MapWidth = 800;
        private bool bSnap = true;

        #endregion

        #region Event

        private void frmMain_Load(object sender, EventArgs e)
        {
            pbMap.Width = int.Parse(tbMapWidth.Text.ToString());
            TempObj.pictureBox.MouseDown += new MouseEventHandler(pb_MouseDown);
        }

        private void tbMapWidth_TextChanged(object sender, EventArgs e)
        {
            try
            {
                MapWidth = int.Parse(tbMapWidth.Text.ToString());
                pbMap.Width = MapWidth;                
            }
            catch (System.Exception ex)
            {
                if (ex.Message.Equals("Input string was not in a correct format."))
                {
                    MessageBox.Show("Vui lòng điền giá trị vào ô", "Lưu ý", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }

        private void rdBlack_CheckedChanged(object sender, EventArgs e)
        {
            pbMap.BackColor = Color.Black;
        }

        private void rdBlue_CheckedChanged(object sender, EventArgs e)
        {
            pbMap.BackColor = Color.FromArgb(100, 100, 255);
        }

        private void cbSnap_CheckedChanged(object sender, EventArgs e)
        {
            bSnap = cbSnap.Checked;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void pbBlock_Click(object sender, EventArgs e)
        {
            _IsHandling = true;
            _IsDeleting = false;
            TempObj.pictureBox.Visible = false;
            btDone.Visible = true;

            PictureBox pb = (PictureBox)sender;
            if (pb.Name == pbBlock.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.brick;
                TempObj.kind = (int)BlockKind.BRICK;
            }
            else if (pb.Name == pbCoin.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.coin_empty;
                TempObj.kind = (int)BlockKind.OUTCOIN;
            }
            else if (pb.Name == pbGrassLeft.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.ground_left;
                TempObj.kind = (int)BlockKind.GROUND_LEFT;
            }
            else if (pb.Name == pbGrassMid.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.ground_middle;
                TempObj.kind = (int)BlockKind.GROUND_MIDDLE;
            }
            else if (pb.Name == pbGrassRight.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.ground_right;
                TempObj.kind = (int)BlockKind.GROUND_RIGHT;
            }
            else if (pb.Name == pbDesert.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.ground_under;
                TempObj.kind = (int)BlockKind.GROUND_SOIL;
            }
            else if (pb.Name == pbRock.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.rock;
                TempObj.kind = (int)BlockKind.HARDBRICK;
            }
            else if (pb.Name == pbPipeTop.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.pipe_cap;
                TempObj.kind = (int)BlockKind.PIPE_CAP;
            }
            else if (pb.Name == pbPipeUnder.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.pipe_body;
                TempObj.kind = (int)BlockKind.PIPE_BODY;
            }
            else if (pb.Name == pbCloud.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.cloud;
                TempObj.kind = (int)BlockKind.CLOUD;
            }
            else if (pb.Name == pbGrass.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.grass;
                TempObj.kind = (int)BlockKind.GRASS;
            }
            else if (pb.Name == pbTree_Hight.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.tree_high;
                TempObj.kind = (int)BlockKind.HIGHTREE;
            }
            else if (pb.Name == pbTree_Low.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.tree_low;
                TempObj.kind = (int)BlockKind.LOWTREE;
            }
            else if (pb.Name == pbMountain.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.mountain;
                TempObj.kind = (int)BlockKind.MOUNTAIN;
            }
            else if (pb.Name == pbItem_Coin.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.Item_Coin;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_COIN;
            }
            else if (pb.Name == pbItem_Flower.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.Item_Flower;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_GUN;
            }
            else if (pb.Name == pbItem_RedMusrom.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.Item_RedMusrom;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_MUSHROOM;
            }
            else if (pb.Name == pbItem_GreenMusrom.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.Item_GreenMusrom;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_LIFE;
            }
            else if (pb.Name == pbDarkSoil.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.dark_soil;
                TempObj.kind = (int)BlockKind.GROUND_DARK_SOIL;
            }
            else if (pb.Name == pbSoilLeft.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.soil_left;
                TempObj.kind = (int)BlockKind.GROUND_SOIL_LEFT;
            }
            else if (pb.Name == pbSoilRight.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.soil_right;
                TempObj.kind = (int)BlockKind.GROUND_SOIL_RIGHT;
            }
            else if (pb.Name == pbFence.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.fence;
                TempObj.kind = (int)BlockKind.FENCE;
            }
            else if (pb.Name == pbMushRoomEnemy.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.enemy_musroom;
                TempObj.kind = (int)BlockKind.MUSHROOM_ENEMY;
            }
            else if (pb.Name == pbTurleEnemy.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.enemy_turle;
                TempObj.kind = (int)BlockKind.TURLE;
            }
            else if (pb.Name == pbCross.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.cross;
                TempObj.kind = (int)BlockKind.CROSS;
            }
            else if (pb.Name == pbHiddenLife.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.life;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_LIFE_HIDDEN;
            }
            else if (pb.Name == pbCheckPoint.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.check_point;
                TempObj.kind = (int)BlockKind.CHECKPOINT;
            }
            else if (pb.Name == pbPirhanaPlant.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.pirhana_plant;
                TempObj.kind = (int)BlockKind.PIRHANAPLANT;
            }
            else if (pb.Name == pbEndmap.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.end_map;
                TempObj.kind = (int)BlockKind.ENDMAP;
            }
            else if (pb.Name == pbMushRoomGroundRight.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.MushRoomGroundRight;
                TempObj.kind = (int)BlockKind.GROUND_MUSHROOM_RIGHT;
            }
            else if (pb.Name == pbMushRoomGroundLeft.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.MushRoomGroundLeft;
                TempObj.kind = (int)BlockKind.GROUND_MUSHROOM_LEFT;
            }
            else if (pb.Name == pbMushRoomGroundMiddle.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.MushRoomGroundMiddle;
                TempObj.kind = (int)BlockKind.GROUND_MUSHROOM_MIDDLE;
            }
            else if (pb.Name == pbMushRoomGroundUnder.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.GroundUnderMushRoom;
                TempObj.kind = (int)BlockKind.GROUNDUNDERMUSHROOM;
            }
            else if (pb.Name == pbFallingCross.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.FallingCross;
                TempObj.kind = (int)BlockKind.FALLING_CROSS;
            }
            else if (pb.Name == pbBonusStar.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.BrickBonusStar;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_STAR;
            }
            else if (pb.Name == pbRedTurle.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.red_enemy_turle;
                TempObj.kind = (int)BlockKind.RED_TURLE;
            }
        }

        private void pbMap_MouseMove(object sender, MouseEventArgs e)
        {
            if (_IsHandling)
            {

                TempObj.pictureBox.Visible = true;

                int x = 0;// pbMap.Location.X;
                int y = 0;// pbMap.Location.Y;

                //Cai nay la de ve hinh de len hinh khac
                PictureBox pb = (PictureBox)sender;
                if (pb.Name != "pbMap")
                {
                    x = pb.Location.X;
                    y = pb.Location.Y;
                }

                if (bSnap)
                {
                    x += e.X / BlockSize * BlockSize;
                    y += e.Y / BlockSize * BlockSize;
                }
                else
                {
                    x += e.X;
                    y += e.Y;
                }               

                posX.Text = x.ToString();
                posY.Text = y.ToString();

                TempObj.pictureBox.Location = new Point(x, y);
                pbMap.Controls.Add(TempObj.pictureBox);
                TempObj.pictureBox.BringToFront();
                TempObj.x = x;
                TempObj.y = y;
            }            
        }

        private void pb_MouseDown(object sender, MouseEventArgs e)
        {
            if (_IsDeleting)
            {
                if (listPbObject.Count != 0)
                {
                    int i = 1;
                    foreach (pbObject pbobj in listPbObject)
                    {
                        if (pbobj.x == TempObj.x && pbobj.y == TempObj.y)
                        {
                            pbMap.Controls.RemoveAt(i);
                            listPbObject.Remove(pbobj);
                            break;
                        }
                        else
                            i++;
                    }
                }

            }
            else if (_IsHandling)
            {
                int index = 1;
                foreach (pbObject pbobj in listPbObject)
                {
                    if (pbobj.x == TempObj.x && pbobj.y == TempObj.y)
                    {
                        pbMap.Controls.RemoveAt(index);
                        listPbObject.Remove(pbobj);                        
                        break;
                    }
                    else
                        index++;
                }

                pbObject temp = new pbObject();
                temp.x = TempObj.x;
                temp.y = TempObj.y;
                temp.kind = TempObj.kind;

                listPbObject.Add(temp);
                
                PictureBox pb = new PictureBox();
                pb.MouseMove += new MouseEventHandler(pbMap_MouseMove); // Them event vao thi moi de hinh khac len duoc
                pb.Image = TempObj.pictureBox.Image;
                pb.SizeMode = PictureBoxSizeMode.AutoSize;
                pb.Location = new Point(TempObj.x, TempObj.y);
                pb.BringToFront();
                pbMap.Controls.Add(pb);
            }
        }

        private void pbDelete_Click(object sender, EventArgs e)
        {
            _IsDeleting = true;
            _IsHandling = true;
            TempObj.pictureBox.Visible = false;
            TempObj.pictureBox.Image = Properties.Resources.delete;
            btDone.Visible = true;
        }

        private void btDone_Click(object sender, EventArgs e)
        {
            _IsDeleting = false;
            _IsHandling = false;
            TempObj.pictureBox.Visible = false;
            btDone.Visible = false;
        }

        private void btGenerate_Click(object sender, EventArgs e)
        {
            Save();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NewMap();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Open();
        }

        #endregion

        #region Other Method

        private void Save()
        {
            SaveFileDialog save = new SaveFileDialog();
            save.Filter = "txt files (*.txt)|*.txt";
            if (save.ShowDialog() == DialogResult.OK)
            {
                FileStream fs = new FileStream(save.FileName, FileMode.Create);
                StreamWriter sw = new StreamWriter(fs);
                sw.Write(MapWidth);
                sw.Write(" ");
                sw.Write(tbMapLevel1.Text);
                sw.Write(" ");
                sw.Write(tbMapLevel2.Text);
                sw.Write(" ");

                if (rdBlue.Checked)
                    sw.Write("0");
                else
                    sw.Write("1");

                foreach (pbObject obj in listPbObject)
                {
                    sw.Write(" ");
                    sw.Write(obj.kind);
                    sw.Write(" ");
                    sw.Write(obj.x);
                    sw.Write(" ");
                    sw.Write(obj.y);
                }

                sw.Write(" 10 0 4 0 0 300 1"); // Cac thong so cua mario

                //sw.Write(" 10 0 4 0 0 300 1");

                sw.Flush();
                sw.Close();
                fs.Close();
            }
        }

        private void Open()
        {
            NewMap();
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = "txt files (*.txt)|*.txt";
            if (open.ShowDialog() == DialogResult.OK)
            {
                StreamReader strR = new StreamReader(open.FileName);
                String content = strR.ReadToEnd().Trim();
                String[] listObj = content.Split(' ');

                
                tbMapWidth.Text = listObj[0];
                tbMapLevel1.Text = listObj[1];
                tbMapLevel2.Text = listObj[2];

                if (int.Parse(listObj[3]) == 0)
                {
                    rdBlue.Checked = true;
                    rdBlack.Checked = false;
                    pbMap.BackColor = Color.FromArgb(100, 100, 255);
                }
                else
                {
                    rdBlue.Checked = false;
                    rdBlack.Checked = true;
                    pbMap.BackColor = Color.Black;
                }

                for (int i = 4; i < listObj.Length - 7; i += 3)
                {
                    int kind = int.Parse(listObj[i]);
                    int x = int.Parse(listObj[i+1]);
                    int y = int.Parse(listObj[i+2]);
                    DrawObj(kind, x, y);
                }
            }
        }

        private void DrawObj(int kind, int x, int y)
        {
            pbObject temp = new pbObject();
            temp.kind = kind;
            temp.x = x;
            temp.y = y;

            listPbObject.Add(temp);

            PictureBox pb = new PictureBox();
            pb.MouseMove += new MouseEventHandler(pbMap_MouseMove);            
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
        }


        private void NewMap()
        {
            listPbObject.Clear();
            tbMapWidth.Text = "800";
            _IsDeleting = _IsHandling = false;
            pbMap.Controls.Clear();
            pbMap.Width = 800;
            MapWidth = 800;
            tbMapLevel1.Text = "1";
            tbMapLevel2.Text = "1";
            rdBlue.Checked = true;
            pbMap.BackColor = Color.FromArgb(100, 100, 255);
        }
        #endregion
        
    }
}
