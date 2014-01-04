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
            PLAYER_KID  = 10,
            PLAYER_ADULT  = 11,
            BRICK_BONUS_MUSHROOM = 16,
            PLAYER_ADULT_GUN = 18,
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
            GROUNDUNDERMUSHROOM = 45,
            BRICK_BONUS_STAR = 46,
            PIPE_1 = 47,
            PIPE_2 = 48,
            PIPE_3 = 49,
            PIPE_4 = 50,
            PIPE_5 = 51,
            STATIC_CROSS = 52,
            CROSS_DOWN = 53
        }

        private pbObject TempObj = new pbObject();
        private List<pbObject> listPbObject= new List<pbObject>();
        private bool _IsDeleting = false;
        private bool _IsHandling = false;
        private int BlockSize = 32;
        private int MapWidth = 1000;
        private bool bSnap = true;
        private int obj_id = 1;
        private List<CTreeObject> listctreeobj;
        private QuadTree qTree;        

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
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbCoin.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.coin_empty;
                TempObj.kind = (int)BlockKind.OUTCOIN;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbGrassLeft.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.ground_left;
                TempObj.kind = (int)BlockKind.GROUND_LEFT;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbGrassMid.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.ground_middle;
                TempObj.kind = (int)BlockKind.GROUND_MIDDLE;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbGrassRight.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.ground_right;
                TempObj.kind = (int)BlockKind.GROUND_RIGHT;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbDesert.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.ground_under;
                TempObj.kind = (int)BlockKind.GROUND_SOIL;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbRock.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.rock;
                TempObj.kind = (int)BlockKind.HARDBRICK;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }            
            else if (pb.Name == pbPipe1.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.pipe1;
                TempObj.kind = (int)BlockKind.PIPE_1;
                TempObj.width = 64;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbPipe2.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.pipe2;
                TempObj.kind = (int)BlockKind.PIPE_2;
                TempObj.width = 64;
                TempObj.height = 64;
                TempObj.st = true;
            }
            else if (pb.Name == pbPipe3.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.pipe3;
                TempObj.kind = (int)BlockKind.PIPE_3;
                TempObj.width = 64;
                TempObj.height = 96;
                TempObj.st = true;
            }
            else if (pb.Name == pbPipe4.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.pipe4;
                TempObj.kind = (int)BlockKind.PIPE_4;
                TempObj.width = 64;
                TempObj.height = 128;
                TempObj.st = true;
            }
            else if (pb.Name == pbPipe5.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.pipe5;
                TempObj.kind = (int)BlockKind.PIPE_5;
                TempObj.width = 64;
                TempObj.height = 160;
                TempObj.st = true;
            }
            else if (pb.Name == pbCloud.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.cloud;
                TempObj.kind = (int)BlockKind.CLOUD;
                TempObj.width = 64;
                TempObj.height = 45;
                TempObj.st = true;
            }
            else if (pb.Name == pbGrass.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.grass;
                TempObj.kind = (int)BlockKind.GRASS;
                TempObj.width = 64;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbTree_Hight.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.tree_high;
                TempObj.kind = (int)BlockKind.HIGHTREE;
                TempObj.width = 32;
                TempObj.height = 96;
                TempObj.st = true;
            }
            else if (pb.Name == pbTree_Low.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.tree_low;
                TempObj.kind = (int)BlockKind.LOWTREE;
                TempObj.width = 32;
                TempObj.height = 64;
                TempObj.st = true;
            }
            else if (pb.Name == pbMountain.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.mountain;
                TempObj.kind = (int)BlockKind.MOUNTAIN;
                TempObj.width = 310;
                TempObj.height = 128;
                TempObj.st = true;
            }
            else if (pb.Name == pbItem_Coin.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.Item_Coin;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_COIN;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbItem_Flower.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.Item_Flower;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_GUN;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbItem_RedMusrom.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.Item_RedMusrom;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_MUSHROOM;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbItem_GreenMusrom.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.Item_GreenMusrom;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_LIFE;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbDarkSoil.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.dark_soil;
                TempObj.kind = (int)BlockKind.GROUND_DARK_SOIL;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbSoilLeft.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.soil_left;
                TempObj.kind = (int)BlockKind.GROUND_SOIL_LEFT;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbSoilRight.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.soil_right;
                TempObj.kind = (int)BlockKind.GROUND_SOIL_RIGHT;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbFence.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.fence;
                TempObj.kind = (int)BlockKind.FENCE;
                TempObj.width = 140;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbMushRoomEnemy.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.enemy_musroom;
                TempObj.kind = (int)BlockKind.MUSHROOM_ENEMY;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = false;
            }
            else if (pb.Name == pbTurleEnemy.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.enemy_turle;
                TempObj.kind = (int)BlockKind.TURLE;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = false;
            }
            else if (pb.Name == pbCross.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.cross;
                TempObj.kind = (int)BlockKind.CROSS;
                TempObj.width = 96;
                TempObj.height = 18;
                TempObj.st = false;
            }
            else if (pb.Name == pbHiddenLife.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.life;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_LIFE_HIDDEN;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbCheckPoint.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.check_point;
                TempObj.kind = (int)BlockKind.CHECKPOINT;
                TempObj.width = 57;
                TempObj.height = 14;
                TempObj.st = false;
            }
            else if (pb.Name == pbPirhanaPlant.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.pirhana_plant;
                TempObj.kind = (int)BlockKind.PIRHANAPLANT;
                TempObj.width = 25;
                TempObj.height = 37;
                TempObj.st = true;
            }
            else if (pb.Name == pbEndmap.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.end_map;
                TempObj.kind = (int)BlockKind.ENDMAP;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbMushRoomGroundRight.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.MushRoomGroundRight;
                TempObj.kind = (int)BlockKind.GROUND_MUSHROOM_RIGHT;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbMushRoomGroundLeft.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.MushRoomGroundLeft;
                TempObj.kind = (int)BlockKind.GROUND_MUSHROOM_LEFT;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbMushRoomGroundMiddle.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.MushRoomGroundMiddle;
                TempObj.kind = (int)BlockKind.GROUND_MUSHROOM_MIDDLE;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbMushRoomGroundUnder.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.GroundUnderMushRoom;
                TempObj.kind = (int)BlockKind.GROUNDUNDERMUSHROOM;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }            
            else if (pb.Name == pbBonusStar.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.BrickBonusStar;
                TempObj.kind = (int)BlockKind.BRICK_BONUS_STAR;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = true;
            }
            else if (pb.Name == pbRedTurle.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.red_enemy_turle;
                TempObj.kind = (int)BlockKind.RED_TURLE;
                TempObj.width = 32;
                TempObj.height = 32;
                TempObj.st = false;
            }
            else if (pb.Name == pbMarioKid.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.mario_kid;
                TempObj.kind = (int)BlockKind.PLAYER_KID;
                TempObj.width = 26;
                TempObj.height = 26;
                TempObj.st = false;
            }
            else if (pb.Name == pbMarioAdult.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.mario_adult;
                TempObj.kind = (int)BlockKind.PLAYER_ADULT;
                TempObj.width = 25;
                TempObj.height = 48;
                TempObj.st = false;
            }
            else if (pb.Name == pbMarioAdultGun.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.mario_gun;
                TempObj.kind = (int)BlockKind.PLAYER_ADULT_GUN;
                TempObj.width = 25;
                TempObj.height = 28;
                TempObj.st = false;
            }
            else if (pb.Name == pbStaticCross.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.cross;
                TempObj.kind = (int)BlockKind.STATIC_CROSS;
                TempObj.width = 96;
                TempObj.height = 18;
                TempObj.st = true;
            }
            else if (pb.Name == pbStaticCross.Name)
            {
                TempObj.pictureBox.Image = Properties.Resources.cross;
                TempObj.kind = (int)BlockKind.CROSS_DOWN;
                TempObj.width = 96;
                TempObj.height = 18;
                TempObj.st = true;
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

                int yTemp = 600 - y;
                posX.Text = x.ToString();
                posY.Text = yTemp.ToString();

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
                temp.id = obj_id;
                temp.x = TempObj.x;
                temp.y = TempObj.y;
                temp.kind = TempObj.kind;
                temp.width = TempObj.width;
                temp.height = TempObj.height;
                temp.st = TempObj.st;

                //MessageBox.Show(TempObj.width.ToString() + " - " + TempObj.height.ToString());
                listPbObject.Add(temp);
                obj_id++;

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
                
                sw.Write(" " + txtNextMap.Text);

                //sw.WriteLine();

                listctreeobj = new List<CTreeObject>();
                foreach (pbObject obj in listPbObject)
                {
                    CTreeObject temp = new CTreeObject();
                    temp.left = obj.x;
                    temp.top = obj.y;
                    temp.bottom = temp.top + obj.height;
                    temp.right = temp.left + obj.width;
                    temp.target = obj;
                    if (temp.target.st == true)
                    {                        
                        listctreeobj.Add(temp);
                    }                      
                    
                    sw.Write(" ");
                    sw.Write(obj.id);
                    sw.Write(" ");
                    sw.Write(obj.kind);
                    sw.Write(" ");
                    sw.Write(obj.x);
                    sw.Write(" ");
                    sw.Write(600 - obj.y);
                    if (obj.kind == (int)BlockKind.BRICK_BONUS_MUSHROOM || obj.kind == (int)BlockKind.BRICK_BONUS_GUN
                        || obj.kind == (int)BlockKind.BRICK_BONUS_LIFE || obj.kind == (int)BlockKind.BRICK_BONUS_COIN
                        || obj.kind == (int)BlockKind.BRICK_BONUS_STAR || obj.kind == (int)BlockKind.BRICK_BONUS_LIFE_HIDDEN)
                    {
                        sw.Write(" ");
                        sw.Write(0);                        
                    }
                    if (obj.kind == (int)BlockKind.PLAYER_KID || obj.kind == (int)BlockKind.PLAYER_ADULT || obj.kind == (int)BlockKind.PLAYER_ADULT_GUN)
                    {
                        // 0 last check point, 4 
                        sw.Write(" 0 4 0 0 300");
                    }
                    
                    sw.WriteLine();
                }                
                
                sw.Flush();
                sw.Close();
                fs.Close();

                BuildQuadTree(MapWidth, listctreeobj, save.FileName);
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

                txtNextMap.Text = listObj[4];

                for (int i = 5; i < listObj.Length - 1; i += 4)
                {
                    int id = int.Parse(listObj[i]);
                    GetObjId(id);
                    int kind = int.Parse(listObj[i + 1]);
                    int x = int.Parse(listObj[i + 2]);
                    int y = int.Parse(listObj[i + 3]);
                    DrawObj(id, kind, x, y);
                    if (kind == (int)BlockKind.BRICK_BONUS_MUSHROOM || kind == (int)BlockKind.BRICK_BONUS_GUN
                        || kind == (int)BlockKind.BRICK_BONUS_LIFE || kind == (int)BlockKind.BRICK_BONUS_COIN
                        || kind == (int)BlockKind.BRICK_BONUS_STAR || kind == (int)BlockKind.BRICK_BONUS_LIFE_HIDDEN)
                        i += 1;
                    if (kind == (int)BlockKind.PLAYER_KID || kind == (int)BlockKind.PLAYER_ADULT || kind == (int)BlockKind.PLAYER_ADULT_GUN)
                        i += 4;
                }
            }
        }

        private void DrawObj(int id, int kind, int x, int y)
        {
            pbObject temp = new pbObject();
            temp.id = id;
            temp.kind = kind;
            temp.x = x;
            temp.y = 600 - y;           

            PictureBox pb = new PictureBox();
            pb.MouseMove += new MouseEventHandler(pbMap_MouseMove);            
            pb.SizeMode = PictureBoxSizeMode.AutoSize;
            pb.Location = new Point(x, 600 - y);
            pb.BringToFront();

            switch (kind)
            {
                case (int)BlockKind.BRICK: 
                    pb.Image = Properties.Resources.brick;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;                    
                case (int)BlockKind.CLOUD: 
                    pb.Image = Properties.Resources.cloud; 
                    temp.width = 64;
                    temp.height = 45;
                    temp.st = true;
                    break;
                case (int)BlockKind.GRASS: 
                    pb.Image = Properties.Resources.grass;
                    temp.width = 64;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.FENCE: 
                    pb.Image = Properties.Resources.fence;
                    temp.width = 140;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.MUSHROOM_ENEMY: 
                    pb.Image = Properties.Resources.enemy_musroom; 
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = false;
                    break;
                case (int)BlockKind.GROUND_LEFT: 
                    pb.Image = Properties.Resources.ground_left; 
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.GROUND_MIDDLE: 
                    pb.Image = Properties.Resources.ground_middle;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.GROUND_RIGHT: 
                    pb.Image = Properties.Resources.ground_right;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.PIPE_1:
                    pb.Image = Properties.Resources.pipe1; 
                    temp.width = 64;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.PIPE_2: 
                    pb.Image = Properties.Resources.pipe2;
                    temp.width = 64;
                    temp.height = 64;
                    temp.st = true;
                    break;
                case (int)BlockKind.PIPE_3:
                    pb.Image = Properties.Resources.pipe3;
                    temp.width = 64;
                    temp.height = 96;
                    temp.st = true;
                    break;
                case (int)BlockKind.PIPE_4:
                    pb.Image = Properties.Resources.pipe4;
                    temp.width = 64;
                    temp.height = 128;
                    temp.st = true;
                    break;
                case (int)BlockKind.PIPE_5:
                    pb.Image = Properties.Resources.pipe5;
                    temp.width = 64;
                    temp.height = 160;
                    temp.st = true;
                    break;
                case (int)BlockKind.BRICK_BONUS_MUSHROOM: 
                    pb.Image = Properties.Resources.Item_RedMusrom; 
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.TURLE: pb.Image = Properties.Resources.enemy_turle;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = false;
                    break;
                case (int)BlockKind.BRICK_BONUS_GUN: 
                    pb.Image = Properties.Resources.Item_Flower;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.BRICK_BONUS_LIFE: 
                    pb.Image = Properties.Resources.Item_GreenMusrom;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.BRICK_BONUS_COIN: 
                    pb.Image = Properties.Resources.Item_Coin;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.OUTCOIN: 
                    pb.Image = Properties.Resources.coin_empty;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.HARDBRICK: 
                    pb.Image = Properties.Resources.rock; 
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.PIRHANAPLANT: 
                    pb.Image = Properties.Resources.pirhana_plant;
                    temp.width = 25;
                    temp.height = 37;
                    temp.st = true;
                    break;
                case (int)BlockKind.ENDMAP: 
                    pb.Image = Properties.Resources.end_map; 
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.MOUNTAIN: 
                    pb.Image = Properties.Resources.mountain;
                    temp.width = 310;
                    temp.height = 128;
                    temp.st = true;
                    break;
                case (int)BlockKind.HIGHTREE: 
                    pb.Image = Properties.Resources.tree_high; 
                    temp.width = 32;
                    temp.height = 96;
                    temp.st = true;
                    break;
                case (int)BlockKind.LOWTREE: 
                    pb.Image = Properties.Resources.tree_low;
                    temp.width = 32;
                    temp.height = 64;
                    temp.st = true;
                    break;
                case (int)BlockKind.CHECKPOINT: 
                    pb.Image = Properties.Resources.check_point;
                    temp.width = 57;
                    temp.height = 14;
                    temp.st = false;
                    break;
                case (int)BlockKind.GROUND_SOIL: 
                    pb.Image = Properties.Resources.ground_under;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.GROUND_SOIL_LEFT: 
                    pb.Image = Properties.Resources.soil_left;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.GROUND_SOIL_RIGHT: 
                    pb.Image = Properties.Resources.soil_right;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.GROUND_DARK_SOIL: 
                    pb.Image = Properties.Resources.dark_soil;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.CROSS: 
                    pb.Image = Properties.Resources.cross;
                    temp.width = 96;
                    temp.height = 18;
                    temp.st = false;
                    break;
                case (int)BlockKind.STATIC_CROSS:
                    pb.Image = Properties.Resources.cross_static;
                    temp.width = 96;
                    temp.height = 18;
                    temp.st = false;
                    break;
                case (int)BlockKind.CROSS_DOWN:
                    pb.Image = Properties.Resources.cross_down;
                    temp.width = 96;
                    temp.height = 18;
                    temp.st = false;
                    break;
                case (int)BlockKind.BRICK_BONUS_LIFE_HIDDEN: 
                    pb.Image = Properties.Resources.life; 
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.GROUND_MUSHROOM_RIGHT: 
                    pb.Image = Properties.Resources.MushRoomGroundRight;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.GROUND_MUSHROOM_LEFT: 
                    pb.Image = Properties.Resources.MushRoomGroundLeft;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.GROUND_MUSHROOM_MIDDLE: 
                    pb.Image = Properties.Resources.MushRoomGroundMiddle;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.GROUNDUNDERMUSHROOM: 
                    pb.Image = Properties.Resources.GroundUnderMushRoom;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.BRICK_BONUS_STAR: 
                    pb.Image = Properties.Resources.BrickBonusStar;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = true;
                    break;
                case (int)BlockKind.RED_TURLE: 
                    pb.Image = Properties.Resources.red_enemy_turle;
                    temp.width = 32;
                    temp.height = 32;
                    temp.st = false;
                    break;
                case (int)BlockKind.PLAYER_KID:
                    pb.Image = Properties.Resources.mario_kid;
                    temp.width = 26;
                    temp.height = 26;
                    temp.st = false;
                    break;
                case (int)BlockKind.PLAYER_ADULT:
                    pb.Image = Properties.Resources.mario_adult;
                    temp.width = 25;
                    temp.height = 48;
                    temp.st = false;
                    break;
                case (int)BlockKind.PLAYER_ADULT_GUN:
                    pb.Image = Properties.Resources.mario_gun;
                    temp.width = 25;
                    temp.height = 48;
                    temp.st = false;
                    break;
            }
            //MessageBox.Show(temp.width.ToString() + temp.height, ToString());
            listPbObject.Add(temp);
            pbMap.Controls.Add(pb);
        }
        
        private void NewMap()
        {
            listPbObject.Clear();
            tbMapWidth.Text = "1000";
            _IsDeleting = _IsHandling = false;
            pbMap.Controls.Clear();
            pbMap.Width = 1000;
            MapWidth = 1000;
            tbMapLevel1.Text = "1";
            tbMapLevel2.Text = "1";
            rdBlue.Checked = true;
            pbMap.BackColor = Color.FromArgb(100, 100, 255);
            obj_id = 1;            
        }

        private void BuildQuadTree(int mapwidth, List<CTreeObject> listCT, string filename)
        {
            qTree = new QuadTree(mapwidth, mapwidth, listCT);            
            qTree.Build();
            qTree.Save(filename);
        }

        private void GetObjId(int id)
        {
            if (id >= obj_id)
            {
                obj_id = id + 1;
            }
        }
        #endregion
        
    }
}
