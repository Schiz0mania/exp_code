package MyActionListener;

import Calculator_UI.Main;
import sun.misc.Perf;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Listener implements ActionListener ,DocumentListener{


    //   数据预处理函数+运算函数调用的顶层函数
    public static void Listener_Add(int length) {
        // 利用flag判断计算设计的码数类别 0-原码 1-补码
        int flag=0;

        // 数据预处理
        String b1 = null;
        try {
            b1 = Main.uiField.getText(0, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        String b2 = null;
        try {
            b2 = Main.uiField.getText(length + 3, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }


        if(b1.charAt(0) == 49){
            b1=Performer.Performer_Comp(b1);
            flag=1;
        }
        if(b2.charAt(0) == 49){
            b2=Performer.Performer_Comp(b2);
            flag=1;
        }

        String ans=Performer.Performer_Add(b1,b2);
        if(flag == 1 ){//若表达式为补码形式，则把输出形式转为原码
            ans=Performer.Performer_Comp(ans);
        }

        Performer.Performer_Output(ans);


    }
    public static void Listener_Minus(int length){
        // 利用flag判断计算设计的码数类别 0-原码 1-补码
        int flag=0;

        // 数据预处理
        String b1 = null;
        try {
            b1 = Main.uiField.getText(0, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        String b2 = null;
        try {
            b2 = Main.uiField.getText(length + 3, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        if(b1.charAt(0) == 49){
            b1=Performer.Performer_Comp(b1);
            flag=1;
        }
        if(b2.charAt(0) == 49){
            b2=Performer.Performer_Comp(b2);
            flag=1;
        }

        String ans=Performer.Performer_Minus(b1,b2);
        if(flag == 1 ){//修改输出结果的输出形式
            ans=Performer.Performer_Comp(ans);
        }

        Performer.Performer_Output(ans);

    }
    public static void Listener_Not(int length)  {

        String b1 = null;
        try {
            b1 = Main.uiField.getText(4, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }

        Performer.Performer_Output(Performer.Performer_Not(b1));



    }
    public static void Listener_Comp(int length){
        String b1 = null;
        try {
            b1 = Main.uiField.getText(5, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        if(b1.charAt(0) == 49){
            Performer.Performer_Output(Performer.Performer_Comp(b1));
        }
       else Performer.Performer_Output(b1);//正数补码为其本身
    }
    public static void Listener_And(int length){
        // 数据预处理
        String b1 = null;
        try {
            b1 = Main.uiField.getText(0, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        String b2 = null;
        try {
            b2 = Main.uiField.getText(length + 5, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        System.out.println(b1+"    "+b2);
        Performer.Performer_Output(Performer.Performer_And(b1,b2));
    }
    public static void Listener_Or(int length){
        // 数据预处理
        String b1 = null;
        try {
            b1 = Main.uiField.getText(0, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        String b2 = null;
        try {
            b2 = Main.uiField.getText(length + 4, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        Performer.Performer_Output(Performer.Performer_Or(b1,b2));

    }
    public static void Listener_Xor(int length){
        // 数据预处理
        String b1 = null;
        try {
            b1 = Main.uiField.getText(0, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        String b2 = null;
        try {
            b2 = Main.uiField.getText(length + 5, length);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        Performer.Performer_Output( Performer.Performer_Xor(b1,b2));
    }

    public static void Listener_InputCheck(int Load) throws BadLocationException {
      // 弹出警告对话框
        JOptionPane.showMessageDialog(
                Main.frame,
                "Invalid Operand length!",
                "Error",
                JOptionPane.WARNING_MESSAGE
        );

        //REFRESH
        Runnable run= new Runnable() {
            @Override
            public void run() {
                try {
                    Main.uiField.setText(Main.uiField.getText(0,Load));
                } catch (BadLocationException badLocationException) {
                    badLocationException.printStackTrace();
                }
            }
        };
        SwingUtilities.invokeLater(run);


    }

    public  void InputControl(ActionEvent e) {

        // 0 1输入
        if (e.getActionCommand().equals("0") || e.getActionCommand().equals("1")) {//判断条件待补充，应该是对于双操作数的运算
            Main.uiField.setText(Main.uiField.getText() + e.getActionCommand());

        }

        //输入控制，单操作数
        if (e.getActionCommand().equals("COMP") ||
                e.getActionCommand().equals("NOT") ) {
            //输入控制
            Main.uiField.setText(e.getActionCommand() + " ");
            //事件控制
            if(e.getActionCommand().equals("NOT"))  Main.Flag=5;
            if(e.getActionCommand().equals("COMP")) Main.Flag=6;
        }

        // 输入控制，双运算符
        if(e.getActionCommand().equals("+") ||
                e.getActionCommand().equals("-") ||
                e.getActionCommand().equals("AND")||
                e.getActionCommand().equals("OR")||
                e.getActionCommand().equals("XOR")){

            //事件控制
            if(e.getActionCommand().equals("+"))    Main.Flag=1;
            if(e.getActionCommand().equals("AND"))  Main.Flag=3;
            if(e.getActionCommand().equals("OR"))  Main.Flag=4;
            if(e.getActionCommand().equals("XOR")) Main.Flag=7;
            if(e.getActionCommand().equals("-")) Main.Flag=2;
            //输入控制
            Main.uiField.setText(Main.uiField.getText()+" "+e.getActionCommand()+" ");



        }

        // 输入控制，“=”号
        if(e.getActionCommand().equals("=")){
            Main.uiField.setText(Main.uiField.getText()+" "+e.getActionCommand()+" ");
        }

    }
    public static void EventControl(ActionEvent e) throws BadLocationException {
        // ANS
        if (e.getActionCommand().equals("=")) {
            if(Main.Count !=Main.L)
                return;
            if (Main.Flag == 1)//加法
                Listener_Add(Main.L);
            if(Main.Flag == 2)//减法
                Listener_Minus(Main.L);
            if(Main.Flag == 3)//与
                Listener_And(Main.L);
            if(Main.Flag == 5)//取反
                Listener_Not(Main.L);
            if(Main.Flag == 6)//补码
                Listener_Comp(Main.L);
            if(Main.Flag == 4)//或
                Listener_Or(Main.L);
            if(Main.Flag == 7)//异或
                Listener_Xor(Main.L);

            //状态位判断
            Performer.Performer_Judge(Main.uiField.getText(Main.uiField.getText().length()-Main.L,Main.L));

            // 自动刷新状态
            if(Main.status.getText() != null){
                Main.status.setText("ByteLength:" + Main.L + "    A:" + Main.A + "    C:" + Main.C + "    O:" + Main.O + "    P:" + Main.P + "    S:" + Main.S + "    Z:" + Main.Z);//refresh
            }
      }

        //CLR
        if (e.getActionCommand().equals("CLR")) {
            Main.uiField.setText(null);
            //A,C,O,P,S,Z
            Main.A=Main.C=Main.O=Main.P=Main.S=Main.Z=0;
            Main.Count=Main.Load=Main.Flag=0;
            Main.Phase=1;
            // 刷新状态
            if(Main.status.getText() != null){
                Main.status.setText("ByteLength:" + Main.L + "    A:" + Main.A + "    C:" + Main.C + "    O:" + Main.O + "    P:" + Main.P + "    S:" + Main.S + "    Z:" + Main.Z);//refresh
            }

        }

        // st - 状态栏显示
        if (e.getActionCommand().equals("ST")) {

            if(Main.status.getText() == null){
                Main.status.setText("ByteLength:" + Main.L + "    A:" + Main.A + "    C:" + Main.C + "    O:" + Main.O + "    P:" + Main.P + "    S:" + Main.S + "    Z:" + Main.Z);//refresh
            }
            else Main.status.setText(null);


        }

        //SL - 切换运算支持字节长度
        if (e.getActionCommand().equals("SHIFT")) {
            Main.L = (Main.L * 2 % 64 == 0) ? 8 : Main.L * 2;

        // 刷新状态
        if(Main.status.getText() != null){
           Main.status.setText("ByteLength:" + Main.L + "    A:" + Main.A + "    C:" + Main.C + "    O:" + Main.O + "    P:" + Main.P + "    S:" + Main.S + "    Z:" + Main.Z);//refresh
        }
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {

        InputControl(e);

        try {
            EventControl(e);
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }

    }

    @Override
    public void insertUpdate(DocumentEvent e) {
        Document doc =e.getDocument();
        String s=null;
        try {
            s=doc.getText(0,doc.getLength());
        } catch (BadLocationException badLocationException) {
            badLocationException.printStackTrace();
        }
        if(s != null){
            //双操作符检测
            if(s.charAt(0) == 49 || s.charAt(0) == 48){
                if(s.charAt(s.length()-1) == 49 || s.charAt(s.length()-1) == 48){
                    Main.Count++;
                }
                // 第一个操作数检测
                if((Main.Phase == 1 && Main.Flag != 0)&&(s.charAt(s.length()-2) != 48 || s.charAt(s.length()-2) != 49 )){
                    if(Main.Count != Main.L){
                        //报错
                        try {
                            Listener_InputCheck(Main.Load);
                        } catch (BadLocationException badLocationException) {
                            badLocationException.printStackTrace();
                        }
                        Main.Phase=1;
                        Main.Flag=0;
                        Main.Count=0;
                        Main.Load=0;

                    }
                    else{
                        Main.Phase=2;
                        Main.Count=0;
                        Main.Load=0;
                    }
                }

                //第二个操作数检测
                if( Main.Phase == 2  ){
                    if(Main.Load == 0) Main.Load=s.length();
                    if(s.charAt(s.length()-2)-'0' == '='-'0'){
                        if(Main.Count != Main.L){
                            try {
                                Listener_InputCheck(Main.Load);
                            } catch (BadLocationException badLocationException) {
                                badLocationException.printStackTrace();
                            }
                            Main.Count=0;
                            Main.Load=0;
                        }
                    }
                }
            }
            // 单操作符检测
            else{

                if(s.charAt(s.length()-1) == 49 || s.charAt(s.length()-1) == 48 ){
                    if(Main.Load == 0) Main.Load=s.length()-1;
                    Main.Count++;
                }

                if(s.charAt(s.length()-2)-'0' == '='-'0'){
                    if(Main.Count != Main.L){
                        // 报错
                        try {
                            Listener_InputCheck(Main.Load);
                        } catch (BadLocationException badLocationException) {
                            badLocationException.printStackTrace();
                        }
                        Main.Count=0;
                        Main.Load=0;
                    }
                }
            }
        }

    }

    @Override
    public void removeUpdate(DocumentEvent e) {

    }

    @Override
    public void changedUpdate(DocumentEvent e) {



        }


}


