package exp.github.tools;

import java.io.File;

import exp.libs.utils.io.FileUtils;

/**
 * <PRE>
 * 填充器.
 * ------------------------------------
 * 使用 .empty 文件填充指定文件夹下的所有空的子文件夹.
 * 主要是在上传项目到GitHub时用, GitHub不允许上传空文件夹.
 * </PRE>
 * <B>PROJECT：</B> github-fill-empty-dir
 * <B>SUPPORT：</B> EXP
 * @version   1.0 2018-04-28
 * @author    EXP: 272629724@qq.com
 * @since     jdk版本：jdk1.6
 */
public class Filler {

	/**
	 * [填充器] 工具入口
	 * @param args
	 */
	public static void main(String[] args) {
		String prjRootDir = "把此处修改为 [指定项目根目录] 的绝对路径";
		fillEmptyDir(prjRootDir);
	}
	
	
///////////////////////////////////////////////////////////////////////////////
	
	
	/** 用于填充空目录的文件名 */
	private final static String EMPTY_FILE_NAME = "/.empty";
	
	/** 私有化构造函数 */
	protected Filler() {}
	
	/**
	 * 填充空目录
	 * @param dir
	 */
	public static void fillEmptyDir(String dirPath) {
		fillEmptyDir(new File(dirPath));
	}
	
	/**
	 * 填充空目录
	 * @param dir
	 */
	public static void fillEmptyDir(File dir) {
		create(dir);
	}
	
	/**
	 * 递归在每个空目录创建文件
	 * @param file 根目录
	 */
	private static void create(File root) {
		if(root.exists()) {
			if(root.isFile()) {
				// Undo
				
			} else if(root.isDirectory()) {
				File[] files = root.listFiles();
				if(files.length <= 0) {
					String path = root.getAbsolutePath();
					FileUtils.createFile(path.concat(EMPTY_FILE_NAME));
					System.out.println("已填充空文件夹: " + path);
					
				} else {
					for(File file : files) {
						create(file);
					}
				}
			}
		}
	}
	
}
