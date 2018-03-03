package exp.bilibili.plugin;

import exp.libs.utils.other.LogUtils;
import exp.libs.warp.ver.VersionMgr;

/**
 * <PRE>
 * 版本类.
 *  版本信息记录在 ./src/main/resources/.verinfo 中, 请勿删除该文件.
 * </PRE>
 * <B>PROJECT：</B> exp-libs
 * <B>SUPPORT：</B> EXP
 * @version   1.0 2017-12-17
 * @author    EXP: 272629724@qq.com
 * @since     jdk版本：jdk1.6
 */
public class Version {

	/**
	 * 版本管理入口, 任何项目均不需修改此代码.
	 * @param args 入口参数（win下默认为-m, linux下强制为-p）
	 * 		[-p] 打印最后的版本信息（DOS界面）
	 * 		[-m] 版本管理（UI界面）
	 */
	public static void main(String[] args) {
		LogUtils.loadLogBackConfig();
		VersionMgr.exec(args);
		
		// TODO
		// WS- 注释  ,OCR  RSA代码整理
		// 模拟APP观看时长	(安卓模拟器抓包？？？  手机节奏风暴不需要验证码)
		// cookie过期后依然在抽奖，此时返回错误  请先登录
		// cookie 过期后没有消除账号登陆，又没提示
		
		// 节奏风暴：多线程抽奖?? 封IP。。。
		// GITHUB HTTPS 的TLS协议为2.0 ?? 无法获取页面源码
		// 在线升级， 升级命令：移动文件，删除文件，添加文件,  压缩包转txt
		// 系统托盘好卡
		// 备份cookie zip
		// 如何获取app的cookie
		// win10系统无法执行小学数据任务(OCR不可用)
	}
	
}
