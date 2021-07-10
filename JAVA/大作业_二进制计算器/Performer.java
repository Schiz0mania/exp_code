package MyActionListener;


import Calculator_UI.Main;

public class Performer {

    public static void Performer_Output(String s){

        Main.uiField.setText(Main.uiField.getText()+s);
    }

    public static String Performer_Add(String b1,String b2){
        String s1 = b1;
        String s2 = b2;
        int Cp=0;//符号位进位
        int Cs=0;//数值最高位进位
        //进位
        int flag = 0;
        StringBuffer sb = new StringBuffer();
        for(int z = s1.length() - 1; z >= 0; z--) {


            // 00 11
            if(s1.charAt(z) == s2.charAt(z)){
                sb.append(flag);
                if(s1.charAt(z) == 48 ) flag=0;
                else flag=1;
            }
            else{//10  01
                if(flag == 1){
                    sb.append("0");
                    flag = 1;
                }
                else {
                    sb.append("1");
                    flag=0;
                }


            }

            // 辅助进位标志判断-----------A
            if(z == Main.L / 2 ) Main.A=flag;


            //提取数值最高位进位
            if(z == 1) Cs=flag;
        }
        //提取最高位进位
        Cp=flag;

        // 判断进位标志-----------C
        if(Cp == 1) Main.C=1;
        else Main.C=0;

        //判断溢出-----------O
        if(Cp == Cs) Main.O=0;
        else Main.O=1;
        //倒置
        sb.reverse();

        return sb.toString();

    }

    public static String Performer_Minus(String b1,String b2){

        // 进位
        int flag=0;
        int Cp=0;//符号位进位
        int Cs=0;//数值最高位进位
        StringBuilder sb=new StringBuilder();
        for(int i=Main.L-1;i>=0;i--){
            // 00 11
            if(b1.charAt(i) == b2.charAt(i)){
                if(flag == 1){
                    sb.append("1");
                    flag=1;

                }
                else {
                    sb.append("0");
                    flag = 0;
                }


            }
            // 10
            if(b1.charAt(i) > b2.charAt(i)){
                if(flag==0)sb.append("1");
                else sb.append("0");
                flag=0;
            }
            // 01
            if(b1.charAt(i) < b2.charAt(i)){
                if(flag == 0) sb.append("1");
                else sb.append("0");
                flag=1;
            }
            // 辅助进位标志判断-----------A
            if(i == Main.L / 2  && flag == 1) Main.A=1;
            else Main.A=0;

            //提取数值最高位进位
            if(i == 1) Cs=flag;

        }
        //提取最高位错位
        Cp=flag;

        // 判断进位标志-----------C
        if(Cp == 1) Main.C=1;
        else Main.C=0;

        //判断溢出-----------O
        if(Cp == Cs) Main.O=0;
        else Main.O=1;

        //倒置
        sb.reverse();
        return sb.toString();



    }

    public static String Performer_Not(String b1){
        //输入读取正确性控制
        StringBuffer sb=new StringBuffer();

        //符号位控制
        sb.append(b1.charAt(0));




        //数值位取反
        for(int i=1;i<b1.length();i++){
            if(b1.charAt(i) == 48) sb.append("1");
            else sb.append("0");
        }



        return sb.toString();
    }

    public static String Performer_Comp(String b1){

        //构建 等字节长度 1
        StringBuffer sb1 = new StringBuffer();
        for(int i=0;i<Main.L-1;i++){
            sb1.append("0");
        }
        sb1.append("1");
        //取反
        b1=Performer_Not(b1);

        //加1 ----- 不用上面的Performer函数，防止死循环
        String s1=sb1.toString();
        String s2=b1;
        int Cp=0;//符号位进位
        int Cs=0;//数值最高位进位
        //进位
        int flag = 0;
        StringBuffer sb = new StringBuffer();
        for(int z = s1.length() - 1; z >= 0; z--) {


            // 00 11
            if(s1.charAt(z) == s2.charAt(z)){
                sb.append(flag);
                if(s1.charAt(z) == 48 ) flag=0;
                else flag=1;
            }
            else{//10  01
                if(flag == 1){
                    sb.append("0");
                    flag = 1;
                }
                else {
                    sb.append("1");
                    flag=0;
                }


            }

            // 辅助进位标志判断-----------A
            if(z == Main.L / 2 ) Main.A=flag;


            //提取数值最高位进位
            if(z == 1) Cs=flag;
        }
        //提取最高位进位
        Cp=flag;
        
        if(Main.Flag == 6){
            // 判断进位标志-----------C
            if(Cp == 1) Main.C=1;
            else Main.C=0;

            //判断溢出-----------O
            if(Cp == Cs) Main.O=0;
            else Main.O=1;
        }

        //倒置
        sb.reverse();
        return sb.toString();

    }

    public static String Performer_And(String b1,String b2){
        StringBuffer sb=new StringBuffer();
        for(int i=0;i<b1.length();i++){
            if( b1.charAt(i) == 48 ||  b2.charAt(i)== 48 ){
                sb.append("0");
            }else sb.append("1");
        }
        return sb.toString();

    }

    public static String Performer_Or(String b1,String b2){
        StringBuffer sb=new StringBuffer();
        for(int i=0;i<b1.length();i++){
            if( b1.charAt(i) == 49 ||  b2.charAt(i)== 49 ){
                sb.append("1");
            }else sb.append("0");
        }
        return sb.toString();
    }

    public static String Performer_Xor(String b1,String b2){
        StringBuffer sb=new StringBuffer();
        for(int i=0;i<b1.length();i++){
            if( b1.charAt(i) ==  b2.charAt(i) ){
                sb.append("0");
            }else sb.append("1");
        }
        return sb.toString();
    }

    // 以下状态位判断不考虑进位/错位问题,可在运算外部调用执行
        public static void Performer_Judge_S(String s){
        if(s.charAt(0) == 48) // 0
            Main.S=0;
        else Main.S=1;
    }
        public static void Performer_Judge_Z(String s){
        for(int i=1;i<Main.L;i++){ // 有符号位二进制不考虑标记位
            if(s.charAt(i) == 49){
                Main.Z=0;
                return;
            }
        }
        Main.Z=1;
    }
        public static void Performer_Judge_P(String s){
        int count=0;
        for(int i=0;i<Main.L;i++){
            if(s.charAt(i) == 49) count++;
        }
        if(count % 2 == 0) Main.P=1;
        else Main.P=0;
    }
    public static void Performer_Judge(String s){
        Performer_Judge_S(s);
        Performer_Judge_Z(s);
        Performer_Judge_P(s);
    }
}
