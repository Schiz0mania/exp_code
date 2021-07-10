package exp_tow;

import javax.swing.*;
import java.applet.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;


public class  EXP extends Applet {
    //设计和编写一个可以用鼠标操作的Applet小应用程序和相应的HTML页面，观察Applet的执行过程，测试程序鼠标用户交互操作的效果。
    public void init(){


        JFrame jf =new JFrame("实验窗口");
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jf.setSize(400,400);
        jf.setLocationRelativeTo(null);


        JPanel panel1 = new JPanel();
        panel1.setSize(100,100);

        JButton btn1= new JButton("OK");
        btn1.setActionCommand("OK");

        btn1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(
                        jf,
                        "你点击了 OK 按钮",
                        "消息标题",
                        JOptionPane.INFORMATION_MESSAGE

                );
            }
        });
        panel1.add(btn1);

        JPanel panel3 = new JPanel();
        panel3.setSize(100,100);

        JTextField jt=new JTextField("dont touch me");
        jt.setBackground(Color.ORANGE);
        jt.setVisible(true);
        jt.setSize(100,100);
        jt.addMouseListener(new MouseListener() {
            @Override
            public void mouseClicked(MouseEvent e) {

            }

            @Override
            public void mousePressed(MouseEvent e) {

            }

            @Override
            public void mouseReleased(MouseEvent e) {

            }

            @Override
            public void mouseEntered(MouseEvent e) {
                JOptionPane.showMessageDialog(
                        jf,
                        "i said dont touch me",
                        "消息标题",
                        JOptionPane.INFORMATION_MESSAGE

                );

            }

            @Override
            public void mouseExited(MouseEvent e) {


            }
        });

        panel3.add(jt);

        JPanel panel2 = new JPanel();
        panel2.setSize(100,100);

        JButton btn2=new JButton("CANCEL");
        btn2.setActionCommand("CANCEL");

        btn2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                JOptionPane.showMessageDialog(
                        jf,
                        "你点击了 CANCEL 按钮",
                        "消息标题",
                        JOptionPane.INFORMATION_MESSAGE

                );
            }
        });
        panel2.add(btn2);

        Box vBox = Box.createVerticalBox();
        vBox.add(panel1);
        vBox.add(panel3);
        vBox.add(panel2);



        jf.setVisible(true);
        jf.setContentPane(vBox);


    }
}

