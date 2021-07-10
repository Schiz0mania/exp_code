package Calculator_UI;


import MyActionListener.Listener;



import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;

import java.awt.*;


    public class Main {

    //UI组件
    public static JFrame frame ;
    public static JTextField uiField ;//输出输出区域
    public static JLabel status;//运算状态栏
    public static JButton shift_btn;
    public static JButton zero_btn;
    public static JButton one_btn;
    public static JButton plus_btn;
    public static JButton minus_btn ;
    public static JButton AND_btn;
    public static JButton OR_btn ;
    public static JButton NOT_btn;
    public static JButton COMP_btn;
    public static JButton XOR_btn;
    public static JButton ST_btn ;
    public static JButton CLR_btn;
    public static JButton ANS_btn ;
    //状态量
    public static int Flag,L,Count,Load,Phase; // Flag-控制运算，L字节长度,Count计数器，Load帮助记录回撤点,Phase用来控制多操作数的输入检测
    public static int A,C,O,P,S,Z;//A,C,O,P,S,Z六个状态标记符
    // UI
    public static void init(){
        //状态值初始化
        L=8;
        Flag=0;
        Count=0;
        Load = 0;
        Phase=1;


        //组件初始化
        frame=new JFrame("Binary Calculator");
        uiField = new JTextField();
        status = new JLabel();
        status.setText(null);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setLayout(null);
        frame.setSize(450,200);

//---------------------------------------box1
        //-----------------------box01:

        //输出输出区域
        uiField.setSize(400,100);


        //状态栏
        status.setBackground(Color.WHITE);
        status.setSize(400,25);

        Box vbox01 = Box.createVerticalBox();
        vbox01.add(uiField);
        vbox01.add(status);

        //-----------------------box02
        ST_btn = new JButton("ST");//更新结果状态
            ST_btn.setActionCommand("ST");
        zero_btn= new JButton("0");
            zero_btn.setPreferredSize(new Dimension(60,20));
            zero_btn.setActionCommand("0");
        one_btn = new JButton("1");
            one_btn.setPreferredSize(new Dimension(60,20));
            one_btn.setActionCommand("1");

        Box vbox02=Box.createVerticalBox();
        vbox02.setSize(200,600);
        vbox02.add(ST_btn);
        vbox02.add(zero_btn);
        vbox02.add(one_btn);
        Box hbox1=Box.createHorizontalBox();
        hbox1.add(vbox01);
        hbox1.add(vbox02);

//---------------------------------------box2
        plus_btn= new JButton("+");
            plus_btn.setActionCommand("+");
        minus_btn = new JButton("-");
            minus_btn.setActionCommand("-");
        Box vbox11=Box.createVerticalBox();
        vbox11.add(plus_btn);
        vbox11.add(minus_btn);

        AND_btn= new JButton("AND");
            AND_btn.setActionCommand("AND");
        OR_btn = new JButton("OR");
            OR_btn.setActionCommand("OR");
        Box vbox12=Box.createVerticalBox();
        vbox12.add(AND_btn);
        vbox12.add(OR_btn);

        NOT_btn= new JButton("NOT");
            NOT_btn.setActionCommand("NOT");
        COMP_btn = new JButton("COMP");
            COMP_btn.setActionCommand("COMP");
        Box vbox13=Box.createVerticalBox();
        vbox13.add(NOT_btn);
        vbox13.add(COMP_btn);

        XOR_btn= new JButton("XOR");
            XOR_btn.setActionCommand("XOR");
        shift_btn=new JButton("SL");//更变字节长度
            shift_btn.setPreferredSize(new Dimension(60,20));
            shift_btn.setActionCommand("SHIFT");

        Box vbox14=Box.createVerticalBox();
        vbox14.add(XOR_btn);
        vbox14.add(shift_btn);

        CLR_btn= new JButton("CLR");
            CLR_btn.setActionCommand("CLR");
        ANS_btn = new JButton("=");
            ANS_btn.setActionCommand("=");
        Box vbox15=Box.createVerticalBox();
        vbox15.add(CLR_btn);
        vbox15.add(ANS_btn);

        Box hbox2=Box.createHorizontalBox();
        hbox2.add(vbox11);
        hbox2.add(vbox12);
        hbox2.add(vbox13);
        hbox2.add(vbox14);
        hbox2.add(vbox15);

//---------------------------------------mainbox
        Box mainbox=Box.createVerticalBox();
        mainbox.add(hbox1);
        mainbox.add(hbox2);

        frame.setContentPane(mainbox);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    public static void actions(){
        ANS_btn.addActionListener(new Listener());
        zero_btn.addActionListener(new Listener());
        one_btn.addActionListener(new Listener());
        plus_btn.addActionListener(new Listener());
        CLR_btn.addActionListener(new Listener());
        shift_btn.addActionListener(new Listener());
        ST_btn.addActionListener(new Listener());
        NOT_btn.addActionListener(new Listener());
        COMP_btn.addActionListener(new Listener());
        AND_btn.addActionListener(new Listener());
        OR_btn.addActionListener(new Listener());
        XOR_btn.addActionListener(new Listener());
        minus_btn.addActionListener(new Listener());

        Document dc= uiField.getDocument();
        dc.addDocumentListener(new Listener());
    }

    public static void main(String [] args){

    init();
    actions();

    }


}
