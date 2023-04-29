
package javaimglib;

import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import javax.imageio.ImageIO;

public class JavaImgLib {
    
    public static final int COLOR_FORMAT_RGB888 = BufferedImage.TYPE_INT_RGB;
    
    public static final int COLOR_FORMAT_BGR888 = BufferedImage.TYPE_INT_BGR;
    
    public static final int COLOR_FORMAT_RGB555 = BufferedImage.TYPE_USHORT_555_RGB;
    
    static String[] fonts = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O",
    "P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9","period",
    "comma","apostrophe", "exclamation","question","hyphen"};

    public static void main(String[] args)throws IOException, FileNotFoundException{
        convertAnimToBMP("scene","res",".png",140,620,438);
    }
    
    public static void WriteImgToBMP(String input, String extension, BufferedImage img)throws IOException, FileNotFoundException{
        
        convertColorFormat(img, COLOR_FORMAT_RGB888);
        
        ImageIO.write(img, extension, new File(input+"."+extension));
    }
    
    public static void convertAnimToBMP(String input, String directory, String extension, int numOfFrames, int newWidth, int newHeight)throws IOException, FileNotFoundException{

        String s = "./"+directory+"/"+input+"0000"+String.valueOf(1)+extension;
        System.out.println(s);
        for(int i = 1; i <= numOfFrames; i++){
            
            File file = new File("dummy_file_name.bmp");
       
            if(i < 10){
                file = new File("./"+directory+"/"+input+"0000"+String.valueOf(i)+extension);
            }
            else if(i >= 10 && i < 100){
                file = new File("./"+directory+"/"+input+"000"+String.valueOf(i)+extension);
            }
            else if(i >= 100 && i < 1000){
                file = new File("./"+directory+"/"+input+"00"+String.valueOf(i)+extension);
            }
            else if(i >= 1000){
                file = new File("./"+directory+"/"+input+"0"+String.valueOf(i)+extension);
            }
            
            BufferedImage img = ImageIO.read(file);
            if(file.exists()){
                img = convertImageSize(img, newWidth, newHeight);
                WriteImgToBMP("./output/"+input+String.valueOf(i),"bmp", img);
            }
        }
    }
    
    public static BufferedImage convertColorFormat(BufferedImage img, int colorFormat){
        if(img.getType() != colorFormat){
            BufferedImage newImage = new BufferedImage(img.getWidth(), img.getHeight(), colorFormat);
            Graphics2D g2 = newImage.createGraphics();
            g2.drawImage(img, 0, 0, null);
            img = newImage;
        }
        return img;
    }
    
    public static BufferedImage convertImageSize(BufferedImage img, int newWidth, int newHeight){
        BufferedImage newImage = new BufferedImage(newWidth, newHeight, img.getType());
        Graphics2D g2 = newImage.createGraphics();
        g2.drawImage(img, 0, 0, newWidth, newHeight, null);
        img = newImage;
        return img;
    }
    
    public static BufferedImage fileToImg(String fileName)throws FileNotFoundException, IOException{
        File file = new File(fileName);
        
        if(file.exists()){
            BufferedImage img = ImageIO.read(file);
            return img;
        }
        else return null;
    }
    
}
