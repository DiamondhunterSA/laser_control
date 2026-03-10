namespace test_faction2
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label_R = new System.Windows.Forms.Label();
            this.label_Z = new System.Windows.Forms.Label();
            this.label_Y = new System.Windows.Forms.Label();
            this.label_X = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.TextBox_homeio = new System.Windows.Forms.TextBox();
            this.TextBox_decel = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.TextBox_accel = new System.Windows.Forms.TextBox();
            this.TextBox_creep = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.TextBox_speed = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.TextBox_lspeed = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.TextBox_units = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.radioButton_R = new System.Windows.Forms.RadioButton();
            this.radioButton_Z = new System.Windows.Forms.RadioButton();
            this.radioButton_Y = new System.Windows.Forms.RadioButton();
            this.radioButton_X = new System.Windows.Forms.RadioButton();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.radioButton5 = new System.Windows.Forms.RadioButton();
            this.radioButton4 = new System.Windows.Forms.RadioButton();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.radioButton_mode1 = new System.Windows.Forms.RadioButton();
            this.button_home = new System.Windows.Forms.Button();
            this.button_stop = new System.Windows.Forms.Button();
            this.button_zero = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.ControlLight;
            this.groupBox1.Controls.Add(this.label_R);
            this.groupBox1.Controls.Add(this.label_Z);
            this.groupBox1.Controls.Add(this.label_Y);
            this.groupBox1.Controls.Add(this.label_X);
            this.groupBox1.Location = new System.Drawing.Point(9, 11);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(350, 93);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "状态显示";
            // 
            // label_R
            // 
            this.label_R.BackColor = System.Drawing.SystemColors.ControlLight;
            this.label_R.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label_R.Location = new System.Drawing.Point(178, 61);
            this.label_R.Name = "label_R";
            this.label_R.Size = new System.Drawing.Size(150, 26);
            this.label_R.TabIndex = 3;
            this.label_R.Text = "r 停止 ：0";
            this.label_R.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label_Z
            // 
            this.label_Z.BackColor = System.Drawing.SystemColors.ControlLight;
            this.label_Z.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label_Z.Location = new System.Drawing.Point(12, 61);
            this.label_Z.Name = "label_Z";
            this.label_Z.Size = new System.Drawing.Size(150, 26);
            this.label_Z.TabIndex = 2;
            this.label_Z.Text = "z 停止 ：0";
            this.label_Z.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label_Y
            // 
            this.label_Y.BackColor = System.Drawing.SystemColors.ControlLight;
            this.label_Y.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label_Y.Location = new System.Drawing.Point(178, 22);
            this.label_Y.Name = "label_Y";
            this.label_Y.Size = new System.Drawing.Size(150, 26);
            this.label_Y.TabIndex = 1;
            this.label_Y.Text = "y 停止 ：0";
            this.label_Y.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label_X
            // 
            this.label_X.BackColor = System.Drawing.SystemColors.ControlLight;
            this.label_X.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label_X.Location = new System.Drawing.Point(12, 21);
            this.label_X.Name = "label_X";
            this.label_X.Size = new System.Drawing.Size(150, 26);
            this.label_X.TabIndex = 0;
            this.label_X.Text = "x 停止 ：0";
            this.label_X.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.label_X.Click += new System.EventHandler(this.label_X_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.TextBox_homeio);
            this.groupBox2.Controls.Add(this.TextBox_decel);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.TextBox_accel);
            this.groupBox2.Controls.Add(this.TextBox_creep);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.TextBox_speed);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.TextBox_lspeed);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.TextBox_units);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Location = new System.Drawing.Point(10, 115);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(161, 282);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "参数设置";
            // 
            // TextBox_homeio
            // 
            this.TextBox_homeio.Location = new System.Drawing.Point(80, 246);
            this.TextBox_homeio.Name = "TextBox_homeio";
            this.TextBox_homeio.Size = new System.Drawing.Size(75, 21);
            this.TextBox_homeio.TabIndex = 18;
            this.TextBox_homeio.Text = "0";
            // 
            // TextBox_decel
            // 
            this.TextBox_decel.Location = new System.Drawing.Point(80, 209);
            this.TextBox_decel.Name = "TextBox_decel";
            this.TextBox_decel.Size = new System.Drawing.Size(75, 21);
            this.TextBox_decel.TabIndex = 17;
            this.TextBox_decel.Text = "0";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(9, 139);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(65, 12);
            this.label7.TabIndex = 13;
            this.label7.Text = "爬行速度：";
            // 
            // TextBox_accel
            // 
            this.TextBox_accel.Location = new System.Drawing.Point(80, 172);
            this.TextBox_accel.Name = "TextBox_accel";
            this.TextBox_accel.Size = new System.Drawing.Size(75, 21);
            this.TextBox_accel.TabIndex = 16;
            this.TextBox_accel.Text = "1000";
            // 
            // TextBox_creep
            // 
            this.TextBox_creep.Location = new System.Drawing.Point(80, 135);
            this.TextBox_creep.Name = "TextBox_creep";
            this.TextBox_creep.Size = new System.Drawing.Size(75, 21);
            this.TextBox_creep.TabIndex = 15;
            this.TextBox_creep.Text = "10";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 253);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 12;
            this.label1.Text = "原点IO：";
            // 
            // TextBox_speed
            // 
            this.TextBox_speed.Location = new System.Drawing.Point(80, 98);
            this.TextBox_speed.Name = "TextBox_speed";
            this.TextBox_speed.Size = new System.Drawing.Size(75, 21);
            this.TextBox_speed.TabIndex = 14;
            this.TextBox_speed.Text = "100";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 215);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 10;
            this.label6.Text = "减速度：";
            // 
            // TextBox_lspeed
            // 
            this.TextBox_lspeed.Location = new System.Drawing.Point(80, 61);
            this.TextBox_lspeed.Name = "TextBox_lspeed";
            this.TextBox_lspeed.Size = new System.Drawing.Size(75, 21);
            this.TextBox_lspeed.TabIndex = 13;
            this.TextBox_lspeed.Text = "0";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(9, 177);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 9;
            this.label5.Text = "加速度：";
            // 
            // TextBox_units
            // 
            this.TextBox_units.Location = new System.Drawing.Point(80, 24);
            this.TextBox_units.Name = "TextBox_units";
            this.TextBox_units.Size = new System.Drawing.Size(75, 21);
            this.TextBox_units.TabIndex = 12;
            this.TextBox_units.Text = "1";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 101);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 12);
            this.label4.TabIndex = 8;
            this.label4.Text = "运行速度：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 63);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 7;
            this.label3.Text = "起始速度：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 6;
            this.label2.Text = "脉冲当量：";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.radioButton_R);
            this.groupBox3.Controls.Add(this.radioButton_Z);
            this.groupBox3.Controls.Add(this.radioButton_Y);
            this.groupBox3.Controls.Add(this.radioButton_X);
            this.groupBox3.Location = new System.Drawing.Point(177, 115);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(176, 70);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "轴选择";
            // 
            // radioButton_R
            // 
            this.radioButton_R.AutoSize = true;
            this.radioButton_R.Location = new System.Drawing.Point(106, 43);
            this.radioButton_R.Name = "radioButton_R";
            this.radioButton_R.Size = new System.Drawing.Size(41, 16);
            this.radioButton_R.TabIndex = 3;
            this.radioButton_R.TabStop = true;
            this.radioButton_R.Text = "R轴";
            this.radioButton_R.UseVisualStyleBackColor = true;
            this.radioButton_R.CheckedChanged += new System.EventHandler(this.radioButton_R_CheckedChanged);
            // 
            // radioButton_Z
            // 
            this.radioButton_Z.AutoSize = true;
            this.radioButton_Z.Location = new System.Drawing.Point(26, 43);
            this.radioButton_Z.Name = "radioButton_Z";
            this.radioButton_Z.Size = new System.Drawing.Size(41, 16);
            this.radioButton_Z.TabIndex = 2;
            this.radioButton_Z.TabStop = true;
            this.radioButton_Z.Text = "Z轴";
            this.radioButton_Z.UseVisualStyleBackColor = true;
            this.radioButton_Z.CheckedChanged += new System.EventHandler(this.radioButton_Z_CheckedChanged);
            // 
            // radioButton_Y
            // 
            this.radioButton_Y.AutoSize = true;
            this.radioButton_Y.Location = new System.Drawing.Point(106, 21);
            this.radioButton_Y.Name = "radioButton_Y";
            this.radioButton_Y.Size = new System.Drawing.Size(41, 16);
            this.radioButton_Y.TabIndex = 1;
            this.radioButton_Y.TabStop = true;
            this.radioButton_Y.Text = "Y轴";
            this.radioButton_Y.UseVisualStyleBackColor = true;
            this.radioButton_Y.CheckedChanged += new System.EventHandler(this.radioButton_Y_CheckedChanged);
            // 
            // radioButton_X
            // 
            this.radioButton_X.AutoSize = true;
            this.radioButton_X.Checked = true;
            this.radioButton_X.Location = new System.Drawing.Point(26, 21);
            this.radioButton_X.Name = "radioButton_X";
            this.radioButton_X.Size = new System.Drawing.Size(41, 16);
            this.radioButton_X.TabIndex = 0;
            this.radioButton_X.TabStop = true;
            this.radioButton_X.Text = "X轴";
            this.radioButton_X.UseVisualStyleBackColor = true;
            this.radioButton_X.CheckedChanged += new System.EventHandler(this.radioButton_X_CheckedChanged);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.radioButton5);
            this.groupBox4.Controls.Add(this.radioButton4);
            this.groupBox4.Controls.Add(this.radioButton3);
            this.groupBox4.Controls.Add(this.radioButton2);
            this.groupBox4.Controls.Add(this.radioButton1);
            this.groupBox4.Controls.Add(this.radioButton_mode1);
            this.groupBox4.Location = new System.Drawing.Point(177, 191);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(177, 206);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "回零模式";
            // 
            // radioButton5
            // 
            this.radioButton5.AutoSize = true;
            this.radioButton5.Location = new System.Drawing.Point(26, 174);
            this.radioButton5.Name = "radioButton5";
            this.radioButton5.Size = new System.Drawing.Size(95, 16);
            this.radioButton5.TabIndex = 5;
            this.radioButton5.TabStop = true;
            this.radioButton5.Text = "原点负向回零";
            this.radioButton5.UseVisualStyleBackColor = true;
            this.radioButton5.CheckedChanged += new System.EventHandler(this.radioButton5_CheckedChanged);
            // 
            // radioButton4
            // 
            this.radioButton4.AutoSize = true;
            this.radioButton4.Location = new System.Drawing.Point(26, 144);
            this.radioButton4.Name = "radioButton4";
            this.radioButton4.Size = new System.Drawing.Size(95, 16);
            this.radioButton4.TabIndex = 4;
            this.radioButton4.TabStop = true;
            this.radioButton4.Text = "原点正向回零";
            this.radioButton4.UseVisualStyleBackColor = true;
            this.radioButton4.CheckedChanged += new System.EventHandler(this.radioButton4_CheckedChanged);
            // 
            // radioButton3
            // 
            this.radioButton3.AutoSize = true;
            this.radioButton3.Checked = true;
            this.radioButton3.Location = new System.Drawing.Point(26, 114);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(125, 16);
            this.radioButton3.TabIndex = 3;
            this.radioButton3.TabStop = true;
            this.radioButton3.Text = "原点负向回零+反找";
            this.radioButton3.UseVisualStyleBackColor = true;
            this.radioButton3.CheckedChanged += new System.EventHandler(this.radioButton3_CheckedChanged);
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(26, 84);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(125, 16);
            this.radioButton2.TabIndex = 2;
            this.radioButton2.TabStop = true;
            this.radioButton2.Text = "原点正向回零+反找";
            this.radioButton2.UseVisualStyleBackColor = true;
            this.radioButton2.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Location = new System.Drawing.Point(26, 54);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(89, 16);
            this.radioButton1.TabIndex = 1;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "z相负向回零";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // radioButton_mode1
            // 
            this.radioButton_mode1.AutoSize = true;
            this.radioButton_mode1.Location = new System.Drawing.Point(26, 24);
            this.radioButton_mode1.Name = "radioButton_mode1";
            this.radioButton_mode1.Size = new System.Drawing.Size(89, 16);
            this.radioButton_mode1.TabIndex = 0;
            this.radioButton_mode1.TabStop = true;
            this.radioButton_mode1.Text = "z相正向回零";
            this.radioButton_mode1.UseVisualStyleBackColor = true;
            this.radioButton_mode1.CheckedChanged += new System.EventHandler(this.radioButton_mode1_CheckedChanged);
            // 
            // button_home
            // 
            this.button_home.Location = new System.Drawing.Point(361, 97);
            this.button_home.Name = "button_home";
            this.button_home.Size = new System.Drawing.Size(83, 30);
            this.button_home.TabIndex = 4;
            this.button_home.Text = "回  零";
            this.button_home.UseVisualStyleBackColor = true;
            this.button_home.Click += new System.EventHandler(this.button_home_Click);
            // 
            // button_stop
            // 
            this.button_stop.Location = new System.Drawing.Point(361, 178);
            this.button_stop.Name = "button_stop";
            this.button_stop.Size = new System.Drawing.Size(83, 30);
            this.button_stop.TabIndex = 5;
            this.button_stop.Text = "停  止";
            this.button_stop.UseVisualStyleBackColor = true;
            this.button_stop.Click += new System.EventHandler(this.button_stop_Click);
            // 
            // button_zero
            // 
            this.button_zero.Location = new System.Drawing.Point(361, 255);
            this.button_zero.Name = "button_zero";
            this.button_zero.Size = new System.Drawing.Size(83, 30);
            this.button_zero.TabIndex = 6;
            this.button_zero.Text = "位置清零";
            this.button_zero.UseVisualStyleBackColor = true;
            this.button_zero.Click += new System.EventHandler(this.button_zero_Click);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlLight;
            this.ClientSize = new System.Drawing.Size(447, 405);
            this.Controls.Add(this.button_zero);
            this.Controls.Add(this.button_stop);
            this.Controls.Add(this.button_home);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "回零测试";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label_R;
        private System.Windows.Forms.Label label_Z;
        private System.Windows.Forms.Label label_Y;
        private System.Windows.Forms.Label label_X;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox TextBox_homeio;
        private System.Windows.Forms.TextBox TextBox_decel;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox TextBox_accel;
        private System.Windows.Forms.TextBox TextBox_creep;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox TextBox_speed;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox TextBox_lspeed;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox TextBox_units;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RadioButton radioButton_R;
        private System.Windows.Forms.RadioButton radioButton_Z;
        private System.Windows.Forms.RadioButton radioButton_Y;
        private System.Windows.Forms.RadioButton radioButton_X;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.RadioButton radioButton5;
        private System.Windows.Forms.RadioButton radioButton4;
        private System.Windows.Forms.RadioButton radioButton3;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.RadioButton radioButton_mode1;
        private System.Windows.Forms.Button button_home;
        private System.Windows.Forms.Button button_stop;
        private System.Windows.Forms.Button button_zero;
        private System.Windows.Forms.Timer timer1;
    }
}

