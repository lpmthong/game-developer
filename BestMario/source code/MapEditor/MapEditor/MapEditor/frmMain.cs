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
                pbMap.Width = int.Parse(tbMapWidth.Text.ToString());
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
            }
            else if (_IsHandling)
            {                

                listPbObject.Add(TempObj);
                
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
        }

        #endregion

        

        

        #region Other Method
        #endregion
    }
}
