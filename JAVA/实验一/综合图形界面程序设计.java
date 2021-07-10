import javax.swing.*;
import java.awt.*;
import java.text.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class EXP {
    public static final double rate = 100/688.0;
    public static void main(String[] args) {


        //窗口
        JFrame jf = new JFrame("人民币 转 美元 窗口");
        jf.setSize(300,200);
        jf.setLocationRelativeTo(null);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        //中间容器
        JPanel panel = new JPanel(new FlowLayout());

        JPanel panel2=new JPanel(new FlowLayout(FlowLayout.CENTER));

        JPanel panel3=new JPanel(new FlowLayout(FlowLayout.CENTER));

        // 标签+文本框
        JLabel jL=new JLabel("人民币数值:");
        jL.setOpaque(true);

        JTextField jt=new JTextField(10);

        //按钮
        JButton jb=new JButton("转换");

        //标签
        JLabel jL2 = new JLabel();
        jL2.setText("对应美元为：");

        jL2.setBackground(Color.yellow);
        jL2.setOpaque(true);

        //按钮 添加事件监听器
        jb.addActionListener(new ActionListener() {
                                 @Override
                                 public void actionPerformed(ActionEvent actionEvent) {
                                     ConvertAction(jt,jL2);
                                 }
                             }


        );

        //布局处理
        panel.add(jL);
        panel.add(jt);

        panel2.add(jb);

        panel3.add(jL2);

        Box vBox = Box.createVerticalBox();
        vBox.add(panel);
        vBox.add(panel2);
        vBox.add(panel3);

        jf.setContentPane(vBox);
        jf.setVisible(true);
    }

    //convert事件处理
    public static void ConvertAction(JTextField jt,JLabel jL){
        Double n=Double.parseDouble(jt.getText()) * rate;

        NumberFormat nf = NumberFormat.getNumberInstance();
        nf.setMaximumFractionDigits(2);

        jL.setText("对应的美元为："+nf.format(n).toString());

    }


}
