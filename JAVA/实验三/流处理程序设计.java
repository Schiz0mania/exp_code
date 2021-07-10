import java.io.*;

public class Main {


    public static void WriteFile(){

        FileOutputStream fos = null;

        try {
            //输出字符到txt文件中
            fos = new FileOutputStream("f:/test/java.txt",false); 

            InputStreamReader is = new InputStreamReader(System.in);
            BufferedReader br = new BufferedReader(is);
            String str = br.readLine();

            //将字符打散成为一个字节数组
            byte[] words = str.getBytes();
            fos.write(words, 0,words.length);
            System.out.println("文件已被更新");


        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }finally{
            try {
                fos.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    public static void ReadFile(){

        FileInputStream fis = null;
        try {

            //再输入txt中的字符，并在控制台输出
            fis = new FileInputStream("f:/test/java.txt");
//			一个字节一个字节读的方法
//			int ch;
//			while((ch=fis.read()) != -1){
//			System.out.print((char)ch);
//			}
            byte[] bytes = new byte[1024];
            int ch;
            //存到数组里读的方法
            //ch表示读了多少字节，如果文件内容为空，则为-1
            //一次读1024
            System.out.println("文件输出：");
            while((ch=fis.read(bytes))!=-1){
                for(int i = 0;i<ch;i++){
                    System.out.print((char)bytes[i]);
                }
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }finally{
            try {
                fis.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    public static void main(String[] args) {
        WriteFile();
        ReadFile();
    }
