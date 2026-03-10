using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using cszmcaux;

namespace test_faction2
{
    public partial class Form1 : Form
    {
        public IntPtr g_handle;         //链接返回的句柄，可以作为卡号
        public int nAxis = 0;           //轴号

        public int home_mode = 4;             //回零模式

        public Form1()
        {
            InitializeComponent();
            //链接控制器 
            zmcaux.ZAux_OpenEth("192.168.0.11", out g_handle);
            if ((int)g_handle != 0)
            {
                MessageBox.Show("控制器链接成功!", "提示");
                timer1.Enabled = true;
            }
            else
            {
                MessageBox.Show("控制器链接失败，请检测IP地址!", "警告");
            }

        }

        //窗口关闭
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            //断开链接
            timer1.Enabled = false;
            zmcaux.ZAux_Close(g_handle);
            g_handle = (IntPtr)0;
        }


        //回零
        private void button_home_Click(object sender, EventArgs e)  
        {
            if ((int)g_handle == 0)
            {
                MessageBox.Show("未链接到控制器!", "提示");
            }
            else
            {
                //设置轴参数
                zmcaux.ZAux_Direct_SetAtype(g_handle, nAxis, 7);        //可以用于Z相回零
                zmcaux.ZAux_Direct_SetUnits(g_handle, nAxis, Convert.ToSingle(TextBox_units.Text));
                zmcaux.ZAux_Direct_SetLspeed(g_handle, nAxis, Convert.ToSingle(TextBox_lspeed.Text));
                zmcaux.ZAux_Direct_SetSpeed(g_handle, nAxis, Convert.ToSingle(TextBox_speed.Text));
                zmcaux.ZAux_Direct_SetAccel(g_handle, nAxis, Convert.ToSingle(TextBox_accel.Text));
                zmcaux.ZAux_Direct_SetDecel(g_handle, nAxis, Convert.ToSingle(TextBox_decel.Text));
                zmcaux.ZAux_Direct_SetCreep(g_handle, nAxis, Convert.ToSingle(TextBox_creep.Text));

                zmcaux.ZAux_Direct_SetDatumIn(g_handle, nAxis, Convert.ToInt32(TextBox_homeio.Text)); //配置原点信号。ZMC系列默认OFF时信号有效，常开传感器需要反转输入口为ON
                zmcaux.ZAux_Direct_SetInvertIn(g_handle, Convert.ToInt32(TextBox_homeio.Text),1);

                zmcaux.ZAux_Direct_Singl_Datum(g_handle, nAxis, home_mode);

            }
        }

        //停止
        private void button_stop_Click(object sender, EventArgs e)
        {
            if ((int)g_handle == 0)
            {
                MessageBox.Show("未链接到控制器!", "提示");
            }
            else
            {
                zmcaux.ZAux_Direct_Singl_Cancel(g_handle, nAxis, 2);
            }
        }

        //位置清零
        private void button_zero_Click(object sender, EventArgs e)
        {
            if ((int)g_handle == 0)
            {
                MessageBox.Show("未链接到控制器!", "提示");
            }
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    zmcaux.ZAux_Direct_SetDpos(g_handle, i, 0);
                }
            }
        }

        //定时器扫描
        private void timer1_Tick(object sender, EventArgs e)
        {
            int[] runstate = new int[4]; 
            float[] curpos = new float[4];

            for (int i = 0; i<4; i++)
            {
                zmcaux.ZAux_Direct_GetIfIdle(g_handle, i, ref runstate[i]);
                zmcaux.ZAux_Direct_GetDpos(g_handle, i, ref curpos[i]);
            }

            label_X.Text = "X " + Convert.ToString(runstate[0] == 0 ? " 运行中 " : " 停止中 ") + curpos[0];
            label_Y.Text = "Y " + Convert.ToString(runstate[1] == 0 ? " 运行中 " : " 停止中 ") + curpos[1];
            label_Z.Text = "Z " + Convert.ToString(runstate[2] == 0 ? " 运行中 " : " 停止中 ") + curpos[2];
            label_R.Text = "R " + Convert.ToString(runstate[3] == 0 ? " 运行中 " : " 停止中 ") + curpos[3];
        }

        //X轴
        private void radioButton_X_CheckedChanged(object sender, EventArgs e)
        {
            nAxis = 0;
            TextBox_homeio.Text = Convert.ToString(0);
        }
        //Y轴
        private void radioButton_Y_CheckedChanged(object sender, EventArgs e)
        {
            nAxis = 1;
            TextBox_homeio.Text = Convert.ToString(1);
        }
        //Z轴
        private void radioButton_Z_CheckedChanged(object sender, EventArgs e)
        {
            nAxis = 2;
            TextBox_homeio.Text = Convert.ToString(2);
        }
        //R轴
        private void radioButton_R_CheckedChanged(object sender, EventArgs e)
        {
            nAxis = 3;
            TextBox_homeio.Text = Convert.ToString(3);
        }

        //模式1
        private void radioButton_mode1_CheckedChanged(object sender, EventArgs e)
        {
            home_mode = 1;
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            home_mode = 2;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            home_mode = 3;
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            home_mode = 4;
        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            home_mode = 8;
        }

        private void radioButton5_CheckedChanged(object sender, EventArgs e)
        {
            home_mode = 9;
        }

        private void label_X_Click(object sender, EventArgs e)
        {

        }


    }
}
